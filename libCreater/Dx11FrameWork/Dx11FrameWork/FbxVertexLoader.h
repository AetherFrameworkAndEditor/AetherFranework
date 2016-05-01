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
		@brief          UV�����擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetVertexUV(FbxMeshNode*, FbxMesh*);

		/*
		@brief          ���_�ʒu�����擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetVertexPosition(FbxMeshNode*, FbxMesh*);
	};
}
#endif