
/******************************************************************************/
/*! @addtogroup aetherClass
@file      FbxLoader.h
@brief     Fbx�t�@�C������̏���ǂݎ��B

*******************************************************************************
@date       2015/12/23
@author     ���{�q
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
		@brief    ���̐ݒ�p
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
		@brief          �t�@�C���ǂݍ��ݗp
		@param[in]		���f���t�@�C���̑��΃p�X
		@param[in]	    ���̐ݒ�
		@return         none
		@exception      none
		*/
		bool Load(std::string, eAxisSystem);

		/*
		@brief          �ǂݍ��񂾃��b�V�������擾
		@param[in]		none
		@return         std::vector<FbxMeshNode>�^�I�u�W�F�N�g
		@exception      none
		*/
		FbxMeshNode& GetNodeMesh(const int);

		int GetMeshNodeCount();
		/*
		@brief          ����p
		@param[in]		none
		@return         none
		@exception      none
		*/
		void Release();
	private:

		/*
		@brief          GetMeshProperty���Ăяo��
		@param[in]		FbxNode�^�I�u�W�F�N�g
		@param[in]		FbxScene�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetMesh(FbxNode*, FbxScene*);

		/*
		@brief          ���b�V���̏ڍ׏����擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@param[in]		FbxScene�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetMeshProperty(FbxMeshNode*, FbxMesh*, FbxScene*);
		
		/*
		@brief          �g�����X�t�H�[�������擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
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