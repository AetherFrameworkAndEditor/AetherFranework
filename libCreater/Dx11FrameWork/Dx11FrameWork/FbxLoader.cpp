#include "FbxLoader.h"
#include "FbxUtility.h"
#include <iostream>

using namespace aetherClass;
using namespace aetherFunction;

	FbxLoader::FbxLoader(){}
	FbxLoader::~FbxLoader()
	{
		Release();
	}
	//
	void FbxLoader::Release(){
		// Release Buffer
		for (auto index : m_meshNodeArray)
		{
			index._vertexBuffer = nullptr;
			index._indexBuffer = nullptr;
			index._materialBuffer.clear();

			SecureZeroMemory(&index._matrix, sizeof(index._matrix));
			SecureZeroMemory(&index._transform, sizeof(index._transform));

			index._vertexCount = NULL;
			index._indexCount = NULL;
		}
	}

	//
	bool FbxLoader::Load(std::string filePath, eAxisSystem axis){
		bool result;

		// Fbx sdk Manager class
		FbxManager* manager = FbxManager::Create();

		FbxIOSettings* iossetings = FbxIOSettings::Create(manager, IOSROOT);
		manager->SetIOSettings(iossetings);

		FbxString lPath = FbxGetApplicationDirectory();
		manager->LoadPluginsDirectory(lPath.Buffer());

		// vertex information accese
		FbxScene* scene = FbxScene::Create(manager, "");

		// this class is fbx file open 
		FbxImporter* importer = FbxImporter::Create(manager, "");

		// Open the fbx file
		result = importer->Initialize(filePath.c_str());
		if (!result)
		{
			return false;
		}

		// Read in fbx infomation
		importer->Import(scene);

		// �C���|�[�^�[�̓t�@�C���J����scene�ɋ��n�����邾��
		// �ȍ~�A�g��Ȃ�����j��
		importer->Destroy();
		importer = nullptr;

		// ���̐ݒ�
		FbxAxisSystem ourAxisSystem = FbxAxisSystem::DirectX;

		if (axis == eAxisSystem::eAxisOpenGL)
		{
			ourAxisSystem = FbxAxisSystem::OpenGL;
			
		}

		// DirectX�n
		FbxAxisSystem sceneAxisSystem = scene->GetGlobalSettings().GetAxisSystem();

		if (sceneAxisSystem != ourAxisSystem)
		{
			FbxAxisSystem::DirectX.ConvertScene(scene);
		}

		// �P�ʌn�̓���
		FbxSystemUnit sceneSystemUnit = scene->GetGlobalSettings().GetSystemUnit();
		if (sceneSystemUnit.GetScaleFactor() != 1.0)
		{
			// �Z���`���[�^�[�P�ʂɃR���o�[�g����
			FbxSystemUnit::cm.ConvertScene(scene);
		}


		//	Get the root node
		FbxNode* rootNode = scene->GetRootNode();

		if (!rootNode)
		{
			return false;
		}

		// �S�Ẵ|���S�����O�p�`��
		TriangulatedPolygons(scene, rootNode);

		// Get the root node child
		const unsigned int childCount = rootNode->GetChildCount();

		for (unsigned int i = 0; i < childCount; i++)
		{
			GetMesh(rootNode->GetChild(i), scene);
		}


		manager->Destroy();
		manager = nullptr;
		return true;
	}

	//
	void FbxLoader::GetMesh(FbxNode* node, FbxScene* scene){

		// Get node attribute 
		FbxNodeAttribute* attribute = node->GetNodeAttribute();
		if (!attribute)
		{
			return;
		}

		switch (attribute->GetAttributeType())
		{
		case FbxNodeAttribute::eMesh:
			// find Mesh!!!
		{
			FbxMesh* mesh = node->GetMesh();

			GetMeshProperty(mesh, scene);
			m_meshNode._keyframeAnimation = GetKeyframeAnimation(scene, node);
			m_meshNodeArray.push_back(m_meshNode);
		}
		break;

		default:

			break;
		}

		// child node Recursive exploration
		const unsigned int childCount = node->GetChildCount();

		for (unsigned int i = 0; i < childCount; ++i)
		{
			GetMesh(node->GetChild(i), scene);
		}
		return;
	}

	// ��������e����ǂݎ��֐����Ăяo��,
	// ���̏����̏I���ɊǗ�����z��Ƀv�b�V������
	void FbxLoader::GetMeshProperty(FbxMesh* mesh, FbxScene* scene){


		GetVertexPosition(mesh);
		GetVertexNomal(mesh);
		GetVertexUV(mesh);
		GetMaterial(mesh);
		GetSkin(mesh, scene);
		GetTransform(mesh);

	
		
	}

	//
	void FbxLoader::GetTransform(FbxMesh* mesh){
		FbxNode* node = mesh->GetNode();
		FbxMeshNode meshNode;
		meshNode._transform._translation = FbxDoubleToVector3(&node->LclTranslation.Get());

		meshNode._transform._rotation = FbxDoubleToVector3(&node->LclRotation.Get());
		meshNode._transform._scale = FbxDoubleToVector3(&node->LclScaling.Get());
		m_meshNode._transform = meshNode._transform;
		return;
	}

	// ���_���W�ʒu�Ȃǂ̎擾
	void FbxLoader::GetVertexPosition(FbxMesh* mesh){

		// Get the all number of vertex
		const unsigned long vertexCount = mesh->GetControlPointsCount();

		// Get the vertex buffer
		FbxVector4* vertex = mesh->GetControlPoints();

		m_meshNode._vertexCount = vertexCount;
		m_meshNode._vertexBuffer = new VertexType[vertexCount]();
		for (int i = 0; i < vertexCount; i++)
		{
			// X,Y,Z���W�擾
			m_meshNode._vertexBuffer[i]._position._x = static_cast<float>(vertex[i][0]);
			m_meshNode._vertexBuffer[i]._position._y = static_cast<float>(vertex[i][1]);
			m_meshNode._vertexBuffer[i]._position._z = static_cast<float>(vertex[i][2]);
		}


		// Get the index buffer
		int* index = mesh->GetPolygonVertices();
		// Get the number of index
		const unsigned long indexCount = mesh->GetPolygonVertexCount();
		m_meshNode._indexCount = indexCount;
		m_meshNode._indexBuffer = new unsigned long[indexCount]();

		for (int i = 0; i < indexCount; i++)
		{

			m_meshNode._indexBuffer[i] = index[i];
		}

		return;
	}

	// �@���擾
	void FbxLoader::GetVertexNomal(FbxMesh* mesh){
		if (!mesh)
		{
			assert(!"���b�V��������܂���");
		}
		Vector3 normalPosition;

		int layerCount = mesh->GetLayerCount();
		for (int index = 0; index < layerCount; ++index)
		{
			FbxLayer* layer = mesh->GetLayer(index);
			FbxLayerElementNormal* normalElement = layer->GetNormals();

			// �@���Ȃ�
			if (!normalElement)
			{
				continue;
			}

			// �@���̐��ƃC���f�b�N�X
			int normalCount = normalElement->GetDirectArray().GetCount();
			int indexCount = normalElement->GetIndexArray().GetCount();

			auto mappingMode = normalElement->GetMappingMode();
			auto referenceMode = normalElement->GetReferenceMode();
			
			//m_normalPosition.reserve(normalCount);
			if (mappingMode == FbxLayerElement::eByPolygonVertex) // �@�������C���f�b�N�X���ƈ�v���Ă���
			{
				if (referenceMode == FbxLayerElement::eDirect)
				{
					int* index = mesh->GetPolygonVertices();
					for (int i = 0; i < normalCount; ++i)
					{
						const int id = index[i];
						
						m_meshNode._vertexBuffer[id]._normal += FbxVector4ToVector3(normalElement->GetDirectArray().GetAt(i));

					}
				}
			}
			else if (mappingMode == FbxLayerElement::eByControlPoint) // �@���������_���ƈ�v���Ă���
			{
				if (referenceMode == FbxLayerElement::eDirect)
				{
					for (int i = 0; i < normalCount; ++i)
					{
						m_meshNode._vertexBuffer[i]._normal = FbxVector4ToVector3(normalElement->GetDirectArray().GetAt(i));

					}
				}
			}

		}

		const int normalizeCount = m_meshNode._vertexCount;
		// �@����W����
		for (int i = 0; i < normalizeCount; ++i)
		{
			m_meshNode._vertexBuffer[i]._normal.Normalize();
		}

		return;
	}

	// UV�擾�֐�
	void FbxLoader::GetVertexUV(FbxMesh* mesh){

		FbxStringList uvSetNameList;

		mesh->GetUVSetNames(uvSetNameList);

		int listCount = uvSetNameList.GetCount();
		for (int uvSetIndex = 0; uvSetIndex < listCount; ++uvSetIndex)
		{
			const char* uvSetName = uvSetNameList.GetStringAt(uvSetIndex);
			const FbxGeometryElementUV* uvElement = mesh->GetElementUV(uvSetName);

			if (!uvElement)
			{
				continue;
			}

			// ����ȊO�Ȃ疳��
			if (uvElement->GetMappingMode() != FbxGeometryElement::eByPolygonVertex&&
				uvElement->GetMappingMode() != FbxGeometryElement::eByControlPoint)
			{
				return;
			}

			// �C���f�b�N�X���g�����g��Ȃ���
			bool useIndex;
			if (uvElement->GetReferenceMode() != FbxGeometryElement::eDirect)
			{
				useIndex = true;
			}
			else
			{
				useIndex = false;
			}

			int indexCount;
			if (useIndex)
			{
				indexCount = uvElement->GetIndexArray().GetCount();
			}
			else
			{
				indexCount = 0;
			}

			const int polygonCount = mesh->GetPolygonCount(); // �|���S���̐����擾

			if (uvElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
			{
				for (int polygonIndex = 0; polygonIndex < polygonCount; ++polygonIndex)
				{
					const int polygonSize = mesh->GetPolygonSize(polygonIndex); // �|���S���̑傫�����擾
					for (int vertexIndex = 0; vertexIndex < polygonSize; ++vertexIndex)
					{
						Vector2 pushValue;
						FbxVector2 uvValue;
						int polygonVertexIndex = mesh->GetPolygonVertex(polygonIndex, vertexIndex);

						int uvIndex;

						if (useIndex)
						{
							uvIndex = uvElement->GetIndexArray().GetAt(polygonVertexIndex);
						}
						else
						{
							uvIndex = polygonVertexIndex;
						}

						uvValue = uvElement->GetDirectArray().GetAt(uvIndex);


						// ��Βl�ɕϊ����Ď擾
						// UV��0.0f~1.0f�̊Ԃł���킳��Ă�͂��Ȃ̂Ń}�C�i�X�̏�Ԃ͂����Ă͂Ȃ�Ȃ�
						pushValue._x = static_cast<float>(abs(uvValue.mData[0]));
						// �㉺�𔽓]�����Ď擾
						pushValue._y = static_cast<float>(abs(1.0f - uvValue.mData[1]));

						m_meshNode._vertexBuffer[vertexIndex]._uv = pushValue;

					}
				}
			}
			else if (uvElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex) 
			{
				int polygonIndexCounter = 0;

				for (int polygonIndex = 0; polygonIndex < polygonCount; ++polygonIndex)
				{
					const int polygonSize = mesh->GetPolygonSize(polygonIndex);
					int* index = mesh->GetPolygonVertices();
					for (int vertexIndex = 0; vertexIndex < polygonSize; ++vertexIndex)
					{
						if (polygonIndexCounter < indexCount)
						{

							Vector2 pushValue;
							FbxVector2 uvValue;

							int uvIndex;
							if (useIndex)
							{
								uvIndex = uvElement->GetIndexArray().GetAt(polygonIndexCounter);
							}
							else
							{
								uvIndex = polygonIndexCounter;
							}

							uvValue = uvElement->GetDirectArray().GetAt(uvIndex);

							pushValue._x = static_cast<float>(abs(uvValue.mData[0]));
							// �㉺�𔽓]�����Ď擾
							pushValue._y = static_cast<float>(abs(1.0f - uvValue.mData[1]));
							polygonIndexCounter += 1;
							const int indexID = index[uvIndex];
							m_meshNode._vertexBuffer[indexID]._uv = pushValue;
						}
					}
				}
			}
		}
		
		return;
	}

	//
	void FbxLoader::GetMaterial(FbxMesh* mesh){
		if (!mesh)return;
		FbxNode* node = mesh->GetNode();

		const int materialCount = node->GetMaterialCount();
		m_meshNode._materialBuffer.resize(materialCount);
		for (int materialID = 0; materialID < materialCount; ++materialID)
		{
			FbxSurfaceMaterial* material = node->GetMaterial(materialID);

			if (!material)
			{
				continue;
			}
			Material destMaterial;

			CopyMaterialData(material, &destMaterial);
			m_meshNode._materialBuffer[materialID] = destMaterial;

		}
		ComputeNodeMatrix(&m_meshNode, node, node->GetScene());
	}

	//
	void FbxLoader::ComputeNodeMatrix(FbxMeshNode* meshNode, FbxNode* node, FbxScene* scene){

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
	void FbxLoader::CopyMaterialData(FbxSurfaceMaterial* material, Material* destMaterial){

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

	//
	FbxKeyframeAnimationInfo FbxLoader::GetKeyframeAnimation(FbxScene* fbxScene, FbxNode* fbxNode){
		bool isAnimated = false;
		FbxKeyframeAnimationInfo outInfomation;

		// �A�j���[�V�����̐����擾
		const int animationCount = fbxScene->GetSrcObjectCount(FbxAnimStack::ClassId);
		for (int animationIndex = 0; animationIndex < animationCount; ++animationIndex)
		{
			FbxAnimStack* animStack = (FbxAnimStack*)fbxScene->GetSrcObject(FbxAnimStack::ClassId, animationIndex);
			FbxAnimEvaluator* animEvaluator = fbxScene->GetAnimationEvaluator();

			// �A�j���[�V�����̖��O���擾
			outInfomation._animationName = animStack->GetName();

			// ���C���[�̐����擾
			const int layerCount = animStack->GetMemberCount();
			for (int layerIndex = 0; layerIndex < layerCount; ++layerIndex)
			{
				FbxAnimLayer* animationLayer = (FbxAnimLayer*)animStack->GetMember(layerIndex);

				// �A�j���[�V�������C���[�̖��O���擾
				outInfomation._animationLayerName = animationLayer->GetName();

				FbxAnimCurve* translationCurve = fbxNode->LclTranslation.GetCurve(animationLayer);
				FbxAnimCurve* rotationCurve = fbxNode->LclRotation.GetCurve(animationLayer);
				FbxAnimCurve* scalingCurve = fbxNode->LclScaling.GetCurve(animationLayer);

				// �g�����X���[�V�����̎擾
				if (translationCurve != 0)
				{
					int keyCount = translationCurve->KeyGetCount();
					for (int keyIndex = 0; keyIndex < keyCount; ++keyIndex)
					{
						FbxTime frameTime = translationCurve->KeyGetTime(keyIndex);
						FbxDouble3 trancelate = fbxNode->EvaluateLocalTranslation(frameTime);
						AnimationVector vector;
						vector._data._x = static_cast<float>(trancelate[0]);
						vector._data._y = static_cast<float>(trancelate[1]);
						vector._data._z = static_cast<float>(trancelate[2]);

						// �t���[������b�P�ʂŎ擾
						vector._frameSecounds = frameTime.GetSecondDouble();
						outInfomation._trancelation.push_back(vector);
					}
				}
				else
				{
					FbxDouble3 translation = fbxNode->LclTranslation.Get();
					AnimationVector vector;

					vector._data._x = static_cast<float>(translation[0]);
					vector._data._y = static_cast<float>(translation[1]);
					vector._data._z = static_cast<float>(translation[2]);
					vector._frameSecounds = 0;

					outInfomation._trancelation.push_back(vector);
				}

				// ���[�e�[�V�����̎擾
				if (rotationCurve != 0)
				{
					int keyCount = rotationCurve->KeyGetCount();
					for (int keyIndex = 0; keyIndex < keyCount; ++keyIndex)
					{
						FbxTime frameTime = rotationCurve->KeyGetTime(keyIndex);
						FbxDouble3 trancelate = fbxNode->EvaluateLocalTranslation(frameTime);
						AnimationVector vector;
						vector._data._x = static_cast<float>(trancelate[0]);
						vector._data._y = static_cast<float>(trancelate[1]);
						vector._data._z = static_cast<float>(trancelate[2]);

						// �t���[������b�P�ʂŎ擾
						vector._frameSecounds = frameTime.GetSecondDouble();
						outInfomation._rotation.push_back(vector);
					}
				}
				else
				{
					FbxDouble3 translation = fbxNode->LclRotation.Get();
					AnimationVector vector;

					vector._data._x = static_cast<float>(translation[0]);
					vector._data._y = static_cast<float>(translation[1]);
					vector._data._z = static_cast<float>(translation[2]);
					vector._frameSecounds = 0;

					outInfomation._rotation.push_back(vector);
				}

				// �X�P�[�����O�̎擾
				if (scalingCurve != 0)
				{
					int keyCount = scalingCurve->KeyGetCount();
					for (int keyIndex = 0; keyIndex < keyCount; ++keyIndex)
					{
						FbxTime frameTime = scalingCurve->KeyGetTime(keyIndex);
						FbxDouble3 trancelate = fbxNode->EvaluateLocalTranslation(frameTime);
						AnimationVector vector;
						vector._data._x = static_cast<float>(trancelate[0]);
						vector._data._y = static_cast<float>(trancelate[1]);
						vector._data._z = static_cast<float>(trancelate[2]);

						// �t���[������b�P�ʂŎ擾
						vector._frameSecounds = frameTime.GetSecondDouble();
						outInfomation._scaling.push_back(vector);
					}
				}
				else
				{
					FbxDouble3 scaling = fbxNode->LclScaling.Get();
					AnimationVector vector;

					vector._data._x = static_cast<float>(scaling[0]);
					vector._data._y = static_cast<float>(scaling[1]);
					vector._data._z = static_cast<float>(scaling[2]);
					vector._frameSecounds = 0;

					outInfomation._scaling.push_back(vector);
				}

			}
		}

		return outInfomation;
	}


	/*
	�}�e���A���̏ڍ׏��擾�֐�
	�e�N�X�`���̐�΃p�X�ƃ}�e���A���F�̎擾

	*/
	FbxDouble3 FbxLoader::GetMaterialPropertey(
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
				std::cout << "this model did not create FbxImplementation" << std::endl;
				return result;
			}
			// �C���v�������e�[�V�����̃��[�g�e�[�u���̎擾
			const FbxBindingTable* rootTable = imolementation->GetRootTable();

			if (!rootTable)
			{
				std::cout << "this model did not create FbxBindingTable" << std::endl;
				return result;
			}

			//�@���[�g�e�[�u���̃G���g���[�̐����擾
			size_t entryCount = rootTable->GetEntryCount();
			for (int index = 0; index < entryCount; ++index)
			{
				// ���[�g�e�[�u���̃G���g���[���擾
				const FbxBindingTableEntry& entry = rootTable->GetEntry(index);

				std::string entryName = entry.GetSource();
				// �G���g���[������v���p�e�B���擾
				FbxProperty entryProperty = material->RootProperty.FindHierarchical(entryName.c_str());

				// �e�N�X�`���̐����擾
				int fileTextureCount = entryProperty.GetSrcObjectCount<FbxFileTexture>();

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

	//
	void FbxLoader::GetSkin(FbxMesh* mesh, FbxScene* scene){

		// �A�j���[�V�������ꗗ���i�[����z��̐錾
		FbxArray<FbxString*> animationNames;

		// �V�[������A�j���[�V�����ꗗ���擾���i�[
		scene->FillAnimStackNameArray(animationNames);

		if (animationNames.Size() == 0)
		{
			return;
		}
		// �A�j���ԍ�0�Ԃ����Ƃ�FbxTakeInfo���擾
		auto takeInfo = scene->GetTakeInfo(animationNames[0]->Buffer());

		// �J�n����
		FbxTime animationStartTime = takeInfo->mLocalTimeSpan.GetStart();

		// �I������
		FbxTime animationEndTime = takeInfo->mLocalTimeSpan.GetStop();

		// �P�ʎ��Ԃ̐ݒ�
		FbxTime periodTime;
		periodTime.SetTime(0, 0, 0, 1, 0, FbxTime::eFrames60);
		// �X�L���̐����擾
		int skinCount = mesh->GetDeformerCount(FbxDeformer::eSkin);

		if (skinCount == 0)
		{
			return;
		}


		for (int skinID = 0; skinID < skinCount; ++skinID)
		{
			// �X�L�����擾
			FbxSkin* skin = static_cast<FbxSkin*>(mesh->GetDeformer(skinID, FbxDeformer::eSkin));

			// �N���X�^�[�̐����擾
			int clusterCount = skin->GetClusterCount();

			for (int clusterID = 0; clusterID < clusterCount; ++clusterID)
			{
				// �N���X�^���擾
				// �N���X�^�i�X�L���ɑΉ������{�̃{�[���̏����Ǘ�����j
				FbxCluster* cluster = skin->GetCluster(clusterID);

				// �{�[�����^���钸�_���̎擾
				int pointCount = cluster->GetControlPointIndicesCount();
				int* pointArray = cluster->GetControlPointIndices();
				double* weigthArray = cluster->GetControlPointWeights();

				if (!pointArray)continue;
				// �{�[���C���f�b�N�X��ǉ�
				int boneIndex = pointArray[clusterID];
				// �{�[�����^���钸�_���ƃE�F�C�g�̎擾
				for (int pointID = 0; pointID < pointCount; ++pointID)
				{
					float weight = static_cast<float>(weigthArray[pointID]);
					BoneImpactInfo boneImpactInfo;
					boneImpactInfo._index = pointArray[pointID];

					auto itr = m_meshNode._skinInfo._boneImpactInfoSet.find(boneImpactInfo);
					if (itr == m_meshNode._skinInfo._boneImpactInfoSet.end())
					{
						// �V�K�ǉ�
						boneImpactInfo.addBoneImpact(clusterID, weight);
						m_meshNode._skinInfo._boneImpactInfoSet.insert(boneImpactInfo);
					}
					else
					{
						// �����ɒǉ�
						//(*itr).addBoneImpact(clusterID, weight);
					}
				}


				int frame = animationEndTime.Get() / periodTime.Get();

				BoneInfo boneInfo;
				boneInfo._name = cluster->GetLink()->GetName();
				boneInfo._frameCount = frame;

				// �{�[���̏����p���s��̎擾
				FbxAMatrix initializeMatrix;
				cluster->GetTransformLinkMatrix(initializeMatrix);
				boneInfo._initialMatrix = aetherFunction::FbxAMatrixToMatrix4x4(initializeMatrix);
				FbxNode* node = cluster->GetLink();

				for (int frameID = 0; frameID < frame; ++frameID)
				{
					Matrix4x4 frameMarix;
					// �t���[�����ƒP�ʎ��Ԃ������Ď��Ԃ��擾
					FbxTime time = frameID*periodTime.Get();

					// �{�[���s��̎擾
					FbxMatrix boneMatrix = node->EvaluateGlobalTransform(time);
					aetherFunction::FbxMatrixToMatrix4x4(&frameMarix, &boneMatrix);
					boneInfo._frameMatrix.push_back(frameMarix);
				}
				m_meshNode._skinInfo._boneInfoAry.push_back(boneInfo);
			}
			
		}
	}

	SkeletonInfo* FbxLoader::FindSkeleton(std::string& skeletonName) {
		auto itr = m_skeletonInfoPool.find(skeletonName);
		if (itr == m_skeletonInfoPool.end()) {
			// �Y������
			return nullptr;
		}

		return itr->second;
	}

	void FbxLoader::GetSkeleton(FbxNode* node, FbxScene* scene){

		FbxNodeAttribute* attribute = node->GetNodeAttribute();

	
	}
	//
	std::vector<FbxMeshNode> FbxLoader::GetNodeMesh(){
		return m_meshNodeArray;
	}