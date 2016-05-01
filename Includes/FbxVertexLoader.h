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

		// UVとインデックスとその頂点の整合性をとる
		void RequlicationVertex(FbxMeshNode*, std::unordered_map<int, std::vector<aetherClass::Vector2>>&);
		/*
		@brief          法線情報を取得
		@param[in]		FbxMesh型オブジェクト
		@return         none
		@exception      none
		*/
		void GetVertexNomal(FbxMeshNode*, FbxMesh*);

		/*
		@brief          UV情報を取得
		@param[in]		FbxMesh型オブジェクト
		@return         none
		@exception      none
		*/
		void GetVertexUV(FbxMeshNode*, FbxMesh*, std::unordered_map<int, std::vector<aetherClass::Vector2>>&);

		/*
		@brief          頂点位置情報を取得
		@param[in]		FbxMesh型オブジェクト
		@return         none
		@exception      none
		*/
		void GetVertexPosition(FbxMeshNode*, FbxMesh*);

	private:
		std::unordered_map<int, std::vector<aetherClass::Vector2>> m_uvBuffer;
		std::vector<int> m_indexNumber;
	};
}
#endif