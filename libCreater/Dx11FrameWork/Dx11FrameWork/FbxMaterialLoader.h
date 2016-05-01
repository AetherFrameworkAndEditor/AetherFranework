#ifndef _FBXMATERIALLOADER_H
#define _FBXMATERIALLOADER_H
#include <fbxsdk.h>
#include "FbxMeshNode.h"
namespace aetherClass{
	class FbxMaterialLoader
	{
	public:
		FbxMaterialLoader();
		~FbxMaterialLoader();

		/*
		@brief          マテリアる情報を取得
		@param[in]		FbxMesh型オブジェクト
		@return         none
		@exception      none
		*/
		void GetMaterial(FbxMeshNode* meshNode, FbxMesh*);

	private:
		/*
		@brief          マテリアル情報を取得
		@param[in]		FbxSurfaceMaterial型オブジェクト
		@param[out]     Material型のオブジェクト
		@return         none
		@exception      none
		*/
		void CopyMaterialData(FbxSurfaceMaterial*, Material*);

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
	};
}
#endif