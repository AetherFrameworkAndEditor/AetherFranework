#include "FbxLoader.h"
#include "FbxUtility.h"
#include <iostream>
#include "FbxKeyFrameLoader.h"
#include "FbxMaterialLoader.h"
#include "FbxVertexLoader.h"
using namespace aetherClass;
using namespace aetherFunction;

	FbxLoader::FbxLoader(){}
	FbxLoader::~FbxLoader()
	{
	}
	//
	void FbxLoader::Release(){
		// Release Buffer

		m_meshNodeArray.clear();
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
			FbxMeshNode meshNode;
			FbxMesh* mesh = node->GetMesh();

			GetMeshProperty(&meshNode,mesh, scene);
			
			FbxKeyFrameLoader keyframe;
			keyframe.GetKeyframeAnimation(&meshNode._keyframeAnimation,scene, node);
			m_meshNodeArray.push_back(meshNode);
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
	void FbxLoader::GetMeshProperty(FbxMeshNode* meshNode,FbxMesh* mesh, FbxScene* scene){


		GetTransform(meshNode,mesh);

		FbxVertexLoader vertex;
		vertex.GetVertex(meshNode, mesh);
	
		FbxMaterialLoader material;
		material.GetMaterial(meshNode,mesh);
		
	}

	//
	void FbxLoader::GetTransform(FbxMeshNode* meshNode, FbxMesh* mesh){
		FbxNode* node = mesh->GetNode();
		meshNode->_transform._translation = FbxDoubleToVector3(&node->LclTranslation.Get());

		meshNode->_transform._rotation = FbxDoubleToVector3(&node->LclRotation.Get());
		meshNode->_transform._scale = FbxDoubleToVector3(&node->LclScaling.Get());
		return;
	}
	//
	std::vector<FbxMeshNode> FbxLoader::GetNodeMesh(){
		return m_meshNodeArray;
	}