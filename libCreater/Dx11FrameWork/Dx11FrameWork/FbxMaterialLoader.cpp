#include "FbxMaterialLoader.h"
#include "FbxUtility.h"
using namespace aetherClass;
using namespace aetherFunction;
FbxMaterialLoader::FbxMaterialLoader()
{
}


FbxMaterialLoader::~FbxMaterialLoader()
{
}

//
void FbxMaterialLoader::GetMaterial(FbxMeshNode* meshNode, FbxMesh* mesh){
	if (!mesh)return;
	FbxNode* node = mesh->GetNode();

	const int materialCount = node->GetMaterialCount();
	meshNode->_materialBuffer.resize(materialCount);
	for (int materialID = 0; materialID < materialCount; ++materialID)
	{
		FbxSurfaceMaterial* material = node->GetMaterial(materialID);

		if (!material){
			continue;
		}

		Material destMaterial;

		CopyMaterialData(material, &destMaterial);
		meshNode->_materialBuffer[materialID] = destMaterial;

	}
	ComputeNodeMatrix(meshNode, node, node->GetScene());
}

//
void FbxMaterialLoader::ComputeNodeMatrix(FbxMeshNode* meshNode, FbxNode* node, FbxScene* scene){

	if (!node || !meshNode)
	{
		return;
	}

	FbxAnimEvaluator* evaluator = scene->GetAnimationEvaluator();
	FbxMatrix global;
	global.SetIdentity();

	if (node != scene->GetRootNode())
	{
		global = evaluator->GetNodeGlobalTransform(node);

		FbxMatrixToMatrix4x4(&meshNode->_matrix, &global);
	}
	else
	{
		FbxMatrixToMatrix4x4(&meshNode->_matrix, &global);
	}
}

/*
�}�e���A���̏��擾�֐����Ăяo��

*/
void FbxMaterialLoader::CopyMaterialData(FbxSurfaceMaterial* material, Material* destMaterial){

	if (!material)
	{
		return;
	}

	if (material->GetClassId().Is(FbxSurfaceLambert::ClassId))
	{
		destMaterial->_type = Material::eFbxMaterialType::eMaterialLambert;
	}
	else if (material->GetClassId().Is(FbxSurfacePhong::ClassId))
	{
		destMaterial->_type = Material::eFbxMaterialType::eMaterialPhong;
	}

	// emmisive
	const FbxDouble3 emmisive = GetMaterialPropertey(material,
		FbxSurfaceMaterial::sEmissive, FbxSurfaceMaterial::sEmissiveFactor, &destMaterial->_emissive);
	destMaterial->_emissive._color = SetFbxColor(emmisive);

	// ambient
	const FbxDouble3 ambient = GetMaterialPropertey(material,
		FbxSurfaceMaterial::sAmbient, FbxSurfaceMaterial::sAmbientFactor, &destMaterial->_ambient);
	destMaterial->_ambient._color = SetFbxColor(ambient);

	// diffuse
	const FbxDouble3 diffuse = GetMaterialPropertey(material,
		FbxSurfaceMaterial::sDiffuse, FbxSurfaceMaterial::sDiffuseFactor, &destMaterial->_diffuse);
	destMaterial->_diffuse._color = SetFbxColor(diffuse);

	// specular
	const FbxDouble3 specular = GetMaterialPropertey(material,
		FbxSurfaceMaterial::sSpecular, FbxSurfaceMaterial::sSpecularFactor, &destMaterial->_specular);
	destMaterial->_specular._color = SetFbxColor(specular);


	FbxProperty tranceparencyFaxtoryProperty = material->FindProperty(FbxSurfaceMaterial::sTransparencyFactor);
	if (tranceparencyFaxtoryProperty.IsValid())
	{
		double tranceparencyFactory = tranceparencyFaxtoryProperty.Get<FbxDouble>();
		destMaterial->_transparencyFactor = static_cast<float>(tranceparencyFactory);
	}

	// Specular Power
	FbxProperty shininessProperty = material->FindProperty(FbxSurfaceMaterial::sShininess);
	if (shininessProperty.IsValid())
	{
		double shininess = shininessProperty.Get<FbxDouble>();
		destMaterial->_shininess = static_cast<float>(shininess);
	}
}

/*
�}�e���A���̏ڍ׏��擾�֐�
�e�N�X�`���̐�΃p�X�ƃ}�e���A���F�̎擾

*/
FbxDouble3 FbxMaterialLoader::GetMaterialPropertey(
	const FbxSurfaceMaterial* material,
	std::string propertyName,
	std::string factorPropertyName,
	MaterialElement* element){

	element->_type = MaterialElement::eMaterialElementType::eElementNone;

	FbxDouble3 result(0, 0, 0);
	const FbxProperty property = material->FindProperty(propertyName.c_str());
	const FbxProperty factorProperty = material->FindProperty(factorPropertyName.c_str());

	if (property.IsValid() && factorProperty.IsValid())
	{

		result = property.Get<FbxDouble3>();
		double factor = factorProperty.Get<FbxDouble>();

		if (factor != 1)
		{
			result[0] *= factor;
			result[1] *= factor;
			result[2] *= factor;
		}

		element->_type = MaterialElement::eMaterialElementType::eElementColor;
	}
	// �e�N�X�`���̃p�X���擾����ۂ̋�؂镶���̐ݒ�
	const char* textureFileSplitChar = "/\\";
	if (property.IsValid())
	{

		int existTextureCount = 0;
		const int textureCount = property.GetSrcObjectCount<FbxFileTexture>();

		for (int i = 0; i < textureCount; ++i)
		{
			FbxFileTexture* fileTexture = property.GetSrcObject<FbxFileTexture>(i);
			if (!fileTexture)
			{
				continue;
			}

			FbxString uvsetName = fileTexture->UVSet.Get();
			std::string uvSetString = uvsetName.Buffer();
			std::string fileFullPath = fileTexture->GetFileName();

			/*
			�e�N�X�`���͐�΃p�X�ł��邽�ߐ�ɐݒ肵����؂镶���ŋ�؂�A
			�t�@�C�����������擾
			*/
			std::string filePath = StringSplite(fileFullPath, textureFileSplitChar[0]);
			filePath = StringSplite(filePath, textureFileSplitChar[1]);

			element->_texturePath.push_back(filePath);

			++existTextureCount;
		}

		const int layerdTextureCount = property.GetDstObjectCount<FbxLayeredTexture>();

		for (int j = 0; j < layerdTextureCount; ++j)
		{
			FbxLayeredTexture* layeredTexture = property.GetSrcObject<FbxLayeredTexture>(j);

			const int textureFileCount = layeredTexture->GetSrcObjectCount<FbxFileTexture>();

			for (int k = 0; k < textureFileCount; ++k)
			{
				FbxFileTexture* fileTexture = layeredTexture->GetSrcObject<FbxFileTexture>(k);

				if (!fileTexture)
				{
					continue;
				}

				FbxString uvsetName = fileTexture->UVSet.Get();
				std::string uvsetString = uvsetName.Buffer();
				std::string fileFullPath = fileTexture->GetFileName();

				std::string filePath = StringSplite(fileFullPath, textureFileSplitChar[0]);
				filePath = StringSplite(filePath, textureFileSplitChar[1]);

				element->_texturePath.push_back(filePath);

				++existTextureCount;
			}
		}

		if (existTextureCount > 0)
		{
			if (element->_type == MaterialElement::eMaterialElementType::eElementColor)
			{
				element->_type = MaterialElement::eMaterialElementType::eElementBoth;
			}
			else
			{
				element->_type = MaterialElement::eMaterialElementType::eElementTexture;
			}
		}

		return result;
	}
	else
	{

		// ������̕��@
		// Unity�����ȊO�ł͂����Ȃ��H�H�H

		// �}�e���A���̃C���v�������e�[�V�������擾
		const FbxImplementation* imolementation = GetImplementation(material, FBXSDK_IMPLEMENTATION_CGFX);

		if (!imolementation)
		{
			return result;
		}
		// �C���v�������e�[�V�����̃��[�g�e�[�u���̎擾
		const FbxBindingTable* rootTable = imolementation->GetRootTable();

		if (!rootTable)
		{
			return result;
		}

		//�@���[�g�e�[�u���̃G���g���[�̐����擾
		size_t entryCount = rootTable->GetEntryCount();
		for (int index = 0; index < entryCount; ++index){

			// ���[�g�e�[�u���̃G���g���[���擾
			const FbxBindingTableEntry& entry = rootTable->GetEntry(index);

			std::string entryName = entry.GetSource();
			
			// �G���g���[������v���p�e�B���擾
			FbxProperty entryProperty = material->RootProperty.FindHierarchical(entryName.c_str());

			// �e�N�X�`���̐����擾
			int fileTextureCount = entryProperty.GetSrcObjectCount<FbxFileTexture>();

			// 
			for (int textureIndex = 0; textureIndex < fileTextureCount; ++textureIndex)
			{
				FbxFileTexture* fileTexture = entryProperty.GetSrcObject<FbxFileTexture>(textureIndex);
				FbxString uvsetName = fileTexture->UVSet.Get();
				std::string uvSetString = uvsetName.Buffer();
				std::string fileFullPath = fileTexture->GetFileName();

				std::string filePath = StringSplite(fileFullPath, textureFileSplitChar[0]);
				filePath = StringSplite(filePath, textureFileSplitChar[1]);

				element->_texturePath.push_back(filePath);
			}

		}
	}
	return result;
}