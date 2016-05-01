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

		// UV�ƃC���f�b�N�X�Ƃ��̒��_�̐��������Ƃ�
		void RequlicationVertex(FbxMeshNode*, std::unordered_map<int, std::vector<aetherClass::Vector2>>&);
		/*
		@brief          �@�������擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetVertexNomal(FbxMeshNode*, FbxMesh*);

		/*
		@brief          UV�����擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetVertexUV(FbxMeshNode*, FbxMesh*, std::unordered_map<int, std::vector<aetherClass::Vector2>>&);

		/*
		@brief          ���_�ʒu�����擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
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