#ifndef _FBXLOADER_H
#define _FBXLOADER_H

#ifndef _FBX_ff
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
		std::vector<FbxMeshNode> GetNodeMesh();

	private:

		/*
		@brief          解放用
		@param[in]		none
		@return         none
		@exception      none
		*/
		void Release();

		/*
		@brief          GetMeshPropertyを呼び出す
		@param[in]		FbxNode型オブジェクト
		@param[in]		FbxScene型オブジェクト
		@return         none
		@exception      none
		*/
		void GetMesh(FbxNode*, FbxScene*);

		/*
		@brief          スケルトン情報を取得
		@param[in]		FbxMesh型オブジェクト
		@param[in]      FbxScene型のオブジェクト
		@return         none
		@exception      none
		*/
		void GetSkeleton(FbxNode*, FbxScene*);

		/*
		@brief          メッシュの詳細情報を取得
		@param[in]		FbxMesh型オブジェクト
		@param[in]		FbxScene型オブジェクト
		@return         none
		@exception      none
		*/
		void GetMeshProperty(FbxMesh*, FbxScene*);
		
		/*
		@brief          トランスフォーム情報を取得
		@param[in]		FbxMesh型オブジェクト
		@return         none
		@exception      none
		*/
		void GetTransform(FbxMesh*);

		/*
		@brief          頂点位置情報を取得
		@param[in]		FbxMesh型オブジェクト
		@return         none
		@exception      none
		*/
		void GetVertexPosition(FbxMesh*);

		/*
		@brief          キーフレームアニメーション取得用
		@param[in]		FbxMesh型オブジェクト
		@return         none
		@exception      none
		*/
		FbxKeyframeAnimationInfo GetKeyframeAnimation(FbxScene*, FbxNode*);
		
		/*
		@brief          法線情報を取得
		@param[in]		FbxMesh型オブジェクト
		@return         none
		@exception      none
		*/
		void GetVertexNomal(FbxMesh*);

		/*
		@brief          UV情報を取得
		@param[in]		FbxMesh型オブジェクト
		@return         none
		@exception      none
		*/
		void GetVertexUV(FbxMesh*);

		/*
		@brief          マテリアる情報を取得
		@param[in]		FbxMesh型オブジェクト
		@return         none
		@exception      none
		*/
		void GetMaterial(FbxMesh*);

		/*
		@brief          スキン情報を取得
		@param[in]		FbxMesh型オブジェクト
		@param[in]      FbxScene型のオブジェクト
		@return         none
		@exception      none
		*/
		void GetSkin(FbxMesh*, FbxScene*);

		

		// スケルトン検索用
		SkeletonInfo* FindSkeleton(std::string& skeletonName);

		/*
		@brief          マテリアル情報を取得
		@param[in]		FbxSurfaceMaterial型オブジェクト
		@param[out]     Material型のオブジェクト
		@return         none
		@exception      none
		*/
		void CopyMaterialData(FbxSurfaceMaterial*,Material*);

		/*
		@brief          マテリアルの詳細情報を取得
		@param[in]		FbxSurfaceMaterial型オブジェクト
		@param[in]      マテリアル種類の名前
		@param[in]      マテリアル種類の名前
		@param[out]     取得したいオブジェクト
		@return         カラー情報を返す
		@exception      none
		*/
		FbxDouble3 GetMaterialPropertey(
			const FbxSurfaceMaterial* material,
			std::string propertyName,
			std::string factorPropertyName,
			MaterialElement* element);

		/*
		@brief          ノードごとの行列取得用
		@param[out]		FbxMeshNode型オブジェクト
		@param[in]      FbxNode型オブジェクト
		@param[in]      FbxScene型オブジェクト
		@return         none
		@exception      none
		*/
		void ComputeNodeMatrix(FbxMeshNode* meshNode, FbxNode* node, FbxScene* scene);
		
	private:

		
		FbxMeshNode m_meshNode;

		std::vector<FbxMeshNode> m_meshNodeArray;

		std::map< std::string, SkeletonInfo* >	m_skeletonInfoPool;	// スケルトンプール
		SkeletonInfo*							m_rootSkeleton;	// ルートスケルトン

		
	};
}

#endif