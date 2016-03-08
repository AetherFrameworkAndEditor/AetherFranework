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

		// インポーターはファイル開いてsceneに橋渡しするだけ
		// 以降、使わないから破棄
		importer->Destroy();
		importer = nullptr;

		// 軸の設定
		FbxAxisSystem ourAxisSystem = FbxAxisSystem::DirectX;

		if (axis == eAxisSystem::eAxisOpenGL)
		{
			ourAxisSystem = FbxAxisSystem::OpenGL;
			
		}

		// DirectX系
		FbxAxisSystem sceneAxisSystem = scene->GetGlobalSettings().GetAxisSystem();

		if (sceneAxisSystem != ourAxisSystem)
		{
			FbxAxisSystem::DirectX.ConvertScene(scene);
		}

		// 単位系の統一
		FbxSystemUnit sceneSystemUnit = scene->GetGlobalSettings().GetSystemUnit();
		if (sceneSystemUnit.GetScaleFactor() != 1.0)
		{
			// センチメーター単位にコンバートする
			FbxSystemUnit::cm.ConvertScene(scene);
		}


		//	Get the root node
		FbxNode* rootNode = scene->GetRootNode();

		if (!rootNode)
		{
			return false;
		}

		// 全てのポリゴンを三角形化
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

	// ここから各情報を読み取る関数を呼び出し,
	// その処理の終わりに管理する配列にプッシュする
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

	// 頂点座標位置などの取得
	void FbxLoader::GetVertexPosition(FbxMesh* mesh){

		// Get the all number of vertex
		const unsigned long vertexCount = mesh->GetControlPointsCount();

		// Get the vertex buffer
		FbxVector4* vertex = mesh->GetControlPoints();

		m_meshNode._vertexCount = vertexCount;
		m_meshNode._vertexBuffer = new VertexType[vertexCount]();
		for (int i = 0; i < vertexCount; i++)
		{
			// X,Y,Z座標取得
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

	// 法線取得
	void FbxLoader::GetVertexNomal(FbxMesh* mesh){
		if (!mesh)
		{
			assert(!"メッシュがありません");
		}
		Vector3 normalPosition;

		int layerCount = mesh->GetLayerCount();
		for (int index = 0; index < layerCount; ++index)
		{
			FbxLayer* layer = mesh->GetLayer(index);
			FbxLayerElementNormal* normalElement = layer->GetNormals();

			// 法線なし
			if (!normalElement)
			{
				continue;
			}

			// 法線の数とインデックス
			int normalCount = normalElement->GetDirectArray().GetCount();
			int indexCount = normalElement->GetIndexArray().GetCount();

			auto mappingMode = normalElement->GetMappingMode();
			auto referenceMode = normalElement->GetReferenceMode();
			
			//m_normalPosition.reserve(normalCount);
			if (mappingMode == FbxLayerElement::eByPolygonVertex) // 法線数がインデックス数と一致している
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
			else if (mappingMode == FbxLayerElement::eByControlPoint) // 法線数が頂点数と一致している
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
		// 法線を標準化
		for (int i = 0; i < normalizeCount; ++i)
		{
			m_meshNode._vertexBuffer[i]._normal.Normalize();
		}

		return;
	}

	// UV取得関数
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

			// これ以外なら無視
			if (uvElement->GetMappingMode() != FbxGeometryElement::eByPolygonVertex&&
				uvElement->GetMappingMode() != FbxGeometryElement::eByControlPoint)
			{
				return;
			}

			// インデックスを使うか使わないか
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

			const int polygonCount = mesh->GetPolygonCount(); // ポリゴンの数を取得

			if (uvElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
			{
				for (int polygonIndex = 0; polygonIndex < polygonCount; ++polygonIndex)
				{
					const int polygonSize = mesh->GetPolygonSize(polygonIndex); // ポリゴンの大きさを取得
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


						// 絶対値に変換して取得
						// UVは0.0f~1.0fの間であらわされてるはずなのでマイナスの状態はあってはならない
						pushValue._x = static_cast<float>(abs(uvValue.mData[0]));
						// 上下を反転させて取得
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
							// 上下を反転させて取得
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
	マテリアルの情報取得関数を呼び出す

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

		// アニメーションの数を取得
		const int animationCount = fbxScene->GetSrcObjectCount(FbxAnimStack::ClassId);
		for (int animationIndex = 0; animationIndex < animationCount; ++animationIndex)
		{
			FbxAnimStack* animStack = (FbxAnimStack*)fbxScene->GetSrcObject(FbxAnimStack::ClassId, animationIndex);
			FbxAnimEvaluator* animEvaluator = fbxScene->GetAnimationEvaluator();

			// アニメーションの名前を取得
			outInfomation._animationName = animStack->GetName();

			// レイヤーの数を取得
			const int layerCount = animStack->GetMemberCount();
			for (int layerIndex = 0; layerIndex < layerCount; ++layerIndex)
			{
				FbxAnimLayer* animationLayer = (FbxAnimLayer*)animStack->GetMember(layerIndex);

				// アニメーションレイヤーの名前を取得
				outInfomation._animationLayerName = animationLayer->GetName();

				FbxAnimCurve* translationCurve = fbxNode->LclTranslation.GetCurve(animationLayer);
				FbxAnimCurve* rotationCurve = fbxNode->LclRotation.GetCurve(animationLayer);
				FbxAnimCurve* scalingCurve = fbxNode->LclScaling.GetCurve(animationLayer);

				// トランスレーションの取得
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

						// フレーム数を秒単位で取得
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

				// ローテーションの取得
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

						// フレーム数を秒単位で取得
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

				// スケーリングの取得
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

						// フレーム数を秒単位で取得
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
	マテリアルの詳細情報取得関数
	テクスチャの絶対パスとマテリアル色の取得

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
		// テクスチャのパスを取得する際の区切る文字の設定
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
				テクスチャは絶対パスでくるため先に設定した区切る文字で区切り、
				ファイル名だけを取得
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

			// もう一つの方法
			// Unityちゃん以外ではつかえない？？？

			// マテリアルのインプリメンテーションを取得
			const FbxImplementation* imolementation = GetImplementation(material, FBXSDK_IMPLEMENTATION_CGFX);

			if (!imolementation)
			{
				std::cout << "this model did not create FbxImplementation" << std::endl;
				return result;
			}
			// インプリメンテーションのルートテーブルの取得
			const FbxBindingTable* rootTable = imolementation->GetRootTable();

			if (!rootTable)
			{
				std::cout << "this model did not create FbxBindingTable" << std::endl;
				return result;
			}

			//　ルートテーブルのエントリーの数を取得
			size_t entryCount = rootTable->GetEntryCount();
			for (int index = 0; index < entryCount; ++index)
			{
				// ルートテーブルのエントリーを取得
				const FbxBindingTableEntry& entry = rootTable->GetEntry(index);

				std::string entryName = entry.GetSource();
				// エントリー名からプロパティを取得
				FbxProperty entryProperty = material->RootProperty.FindHierarchical(entryName.c_str());

				// テクスチャの数を取得
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

		// アニメーション名一覧を格納する配列の宣言
		FbxArray<FbxString*> animationNames;

		// シーンからアニメーション一覧を取得し格納
		scene->FillAnimStackNameArray(animationNames);

		if (animationNames.Size() == 0)
		{
			return;
		}
		// アニメ番号0番をもとにFbxTakeInfoを取得
		auto takeInfo = scene->GetTakeInfo(animationNames[0]->Buffer());

		// 開始時間
		FbxTime animationStartTime = takeInfo->mLocalTimeSpan.GetStart();

		// 終了時間
		FbxTime animationEndTime = takeInfo->mLocalTimeSpan.GetStop();

		// 単位時間の設定
		FbxTime periodTime;
		periodTime.SetTime(0, 0, 0, 1, 0, FbxTime::eFrames60);
		// スキンの数を取得
		int skinCount = mesh->GetDeformerCount(FbxDeformer::eSkin);

		if (skinCount == 0)
		{
			return;
		}


		for (int skinID = 0; skinID < skinCount; ++skinID)
		{
			// スキンを取得
			FbxSkin* skin = static_cast<FbxSkin*>(mesh->GetDeformer(skinID, FbxDeformer::eSkin));

			// クラスターの数を取得
			int clusterCount = skin->GetClusterCount();

			for (int clusterID = 0; clusterID < clusterCount; ++clusterID)
			{
				// クラスタを取得
				// クラスタ（スキンに対応する一本のボーンの情報を管理する）
				FbxCluster* cluster = skin->GetCluster(clusterID);

				// ボーンが与える頂点情報の取得
				int pointCount = cluster->GetControlPointIndicesCount();
				int* pointArray = cluster->GetControlPointIndices();
				double* weigthArray = cluster->GetControlPointWeights();

				if (!pointArray)continue;
				// ボーンインデックスを追加
				int boneIndex = pointArray[clusterID];
				// ボーンが与える頂点情報とウェイトの取得
				for (int pointID = 0; pointID < pointCount; ++pointID)
				{
					float weight = static_cast<float>(weigthArray[pointID]);
					BoneImpactInfo boneImpactInfo;
					boneImpactInfo._index = pointArray[pointID];

					auto itr = m_meshNode._skinInfo._boneImpactInfoSet.find(boneImpactInfo);
					if (itr == m_meshNode._skinInfo._boneImpactInfoSet.end())
					{
						// 新規追加
						boneImpactInfo.addBoneImpact(clusterID, weight);
						m_meshNode._skinInfo._boneImpactInfoSet.insert(boneImpactInfo);
					}
					else
					{
						// 既存に追加
						//(*itr).addBoneImpact(clusterID, weight);
					}
				}


				int frame = animationEndTime.Get() / periodTime.Get();

				BoneInfo boneInfo;
				boneInfo._name = cluster->GetLink()->GetName();
				boneInfo._frameCount = frame;

				// ボーンの初期姿勢行列の取得
				FbxAMatrix initializeMatrix;
				cluster->GetTransformLinkMatrix(initializeMatrix);
				boneInfo._initialMatrix = aetherFunction::FbxAMatrixToMatrix4x4(initializeMatrix);
				FbxNode* node = cluster->GetLink();

				for (int frameID = 0; frameID < frame; ++frameID)
				{
					Matrix4x4 frameMarix;
					// フレーム数と単位時間をかけて時間を取得
					FbxTime time = frameID*periodTime.Get();

					// ボーン行列の取得
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
			// 該当無し
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