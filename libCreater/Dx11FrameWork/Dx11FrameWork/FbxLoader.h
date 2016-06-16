
/******************************************************************************/
/*! @addtogroup aetherClass
@file      FbxLoader.h
@brief     Fbxファイルからの情報を読み取る。

*******************************************************************************
@date       2015/12/23
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _FBXLOADER_H
#define _FBXLOADER_H

#ifndef _FBX_
#define _FBX_
#pragma comment (lib,"libfbxsdk-md.lib")
#include <fbxsdk.h>
#endif

#include "VertexType.h"
#include "FbxMeshNode.h"

namespace aetherClass{

	/*
		@brief    軸の設定用
	*/
	enum class eAxisSystem{
		eAxisDirectX = 0,
		eAxisOpenGL
	};

	class FbxLoader
	{
	public:
		FbxLoader();
		~FbxLoader();

		/*
		@brief          ファイル読み込み用
		@param[in]		モデルファイルの相対パス
		@param[in]	    軸の設定
		@return         none
		@exception      none
		*/
		bool Load(std::string, eAxisSystem);

		/*
		@brief          読み込んだメッシュ情報を取得
		@param[in]		none
		@return         std::vector<FbxMeshNode>型オブジェクト
		@exception      none
		*/
		FbxMeshNode& GetNodeMesh(const int);

		int GetMeshNodeCount();
		/*
		@brief          解放用
		@param[in]		none
		@return         none
		@exception      none
		*/
		void Release();
	private:

		/*
		@brief          GetMeshPropertyを呼び出す
		@param[in]		FbxNode型オブジェクト
		@param[in]		FbxScene型オブジェクト
		@return         none
		@exception      none
		*/
		void GetMesh(FbxNode*, FbxScene*);

		/*
		@brief          メッシュの詳細情報を取得
		@param[in]		FbxMesh型オブジェクト
		@param[in]		FbxScene型オブジェクト
		@return         none
		@exception      none
		*/
		void GetMeshProperty(FbxMeshNode*, FbxMesh*, FbxScene*);
		
		/*
		@brief          トランスフォーム情報を取得
		@param[in]		FbxMesh型オブジェクト
		@return         none
		@exception      none
		*/
		void GetTransform(FbxMeshNode*,FbxMesh*);
	
	private:
		std::vector<FbxMeshNode> m_meshNodeArray;
		FbxImporter* m_importer;
	};
}

#endif