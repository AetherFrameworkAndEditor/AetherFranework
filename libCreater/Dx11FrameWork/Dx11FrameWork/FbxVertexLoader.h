#ifndef _FBXVERTEXLOADEER_H
#define _FBXVERTEXLOADEER_H
#include <fbxsdk.h>
#include "FbxMeshNode.h"
#include <vector>
#include <unordered_map>
namespace aetherClass{
	
	class FbxVertexLoader
	{
	public:
		FbxVertexLoader();
		~FbxVertexLoader();

		void GetVertex(FbxMeshNode*, FbxMesh*);
	private:

		/*
		@brief          UV情報を取得
		@param[in]		FbxMesh型オブジェクト
		@return         none
		@exception      none
		*/
		void GetVertexUV(FbxMeshNode*, FbxMesh*);

		/*
		@brief          頂点位置情報を取得
		@param[in]		FbxMesh型オブジェクト
		@return         none
		@exception      none
		*/
		void GetVertexPosition(FbxMeshNode*, FbxMesh*);
	};
}
#endif