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
		std::vector<FbxMeshNode> GetNodeMesh();

	private:

		/*
		@brief          ����p
		@param[in]		none
		@return         none
		@exception      none
		*/
		void Release();

		/*
		@brief          GetMeshProperty���Ăяo��
		@param[in]		FbxNode�^�I�u�W�F�N�g
		@param[in]		FbxScene�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetMesh(FbxNode*, FbxScene*);

		/*
		@brief          �X�P���g�������擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@param[in]      FbxScene�^�̃I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetSkeleton(FbxNode*, FbxScene*);

		/*
		@brief          ���b�V���̏ڍ׏����擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@param[in]		FbxScene�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetMeshProperty(FbxMesh*, FbxScene*);
		
		/*
		@brief          �g�����X�t�H�[�������擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetTransform(FbxMesh*);

		/*
		@brief          ���_�ʒu�����擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetVertexPosition(FbxMesh*);

		/*
		@brief          �L�[�t���[���A�j���[�V�����擾�p
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		FbxKeyframeAnimationInfo GetKeyframeAnimation(FbxScene*, FbxNode*);
		
		/*
		@brief          �@�������擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetVertexNomal(FbxMesh*);

		/*
		@brief          UV�����擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetVertexUV(FbxMesh*);

		/*
		@brief          �}�e���A������擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetMaterial(FbxMesh*);

		/*
		@brief          �X�L�������擾
		@param[in]		FbxMesh�^�I�u�W�F�N�g
		@param[in]      FbxScene�^�̃I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void GetSkin(FbxMesh*, FbxScene*);

		

		// �X�P���g�������p
		SkeletonInfo* FindSkeleton(std::string& skeletonName);

		/*
		@brief          �}�e���A�������擾
		@param[in]		FbxSurfaceMaterial�^�I�u�W�F�N�g
		@param[out]     Material�^�̃I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void CopyMaterialData(FbxSurfaceMaterial*,Material*);

		/*
		@brief          �}�e���A���̏ڍ׏����擾
		@param[in]		FbxSurfaceMaterial�^�I�u�W�F�N�g
		@param[in]      �}�e���A����ނ̖��O
		@param[in]      �}�e���A����ނ̖��O
		@param[out]     �擾�������I�u�W�F�N�g
		@return         �J���[����Ԃ�
		@exception      none
		*/
		FbxDouble3 GetMaterialPropertey(
			const FbxSurfaceMaterial* material,
			std::string propertyName,
			std::string factorPropertyName,
			MaterialElement* element);

		/*
		@brief          �m�[�h���Ƃ̍s��擾�p
		@param[out]		FbxMeshNode�^�I�u�W�F�N�g
		@param[in]      FbxNode�^�I�u�W�F�N�g
		@param[in]      FbxScene�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void ComputeNodeMatrix(FbxMeshNode* meshNode, FbxNode* node, FbxScene* scene);
		
	private:

		
		FbxMeshNode m_meshNode;

		std::vector<FbxMeshNode> m_meshNodeArray;

		std::map< std::string, SkeletonInfo* >	m_skeletonInfoPool;	// �X�P���g���v�[��
		SkeletonInfo*							m_rootSkeleton;	// ���[�g�X�P���g��

		
	};
}

#endif