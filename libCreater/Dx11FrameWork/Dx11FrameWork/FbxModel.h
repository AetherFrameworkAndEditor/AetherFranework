/******************************************************************************/
/*! @addtogroup aetherClass
@file      FbxModel.h
@brief     Fbx���f���̊��N���X
�@�@�@�@�@�@��{�I�ȃ��f���̕`����ł���

*******************************************************************************
@date       2016/01/15
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _FBXMODEL_H
#define _FBXMODEL_H

#include <memory>
#include "ShaderBase.h"
#include "FbxLoader.h"
#include "DirectXEntity.h"
#include "Mesh.h"
#include "ViewCamera.h"
namespace aetherClass{

	

	class FbxModel:
		DirectXEntity
	{
	public:
		struct Property{
			Transform _transform;
		};
	public:
		 FbxModel::Property property;
	public:
		FbxModel();
		~FbxModel() = default;

		/*
		@brief          FbxFile�̓ǂݍ��݂Ə�����
		@param[in]      Shader�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		bool LoadFBX(std::string, eAxisSystem);

		/*
		@brief          ����p
		@param[in]      Shader�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void Finalize();

		/*
		@brief          �S�Ẵm�[�h�`��p
		@param[in]      Shader�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void Render(ShaderBase*);

		/*
		@brief          �w��m�[�h�̂ݕ`��p�B
		                �͈͊O�̏ꍇ�͂��ׂẴm�[�h��`��
		@param[in]      Shader�I�u�W�F�N�g
		@param[in]      �`�悷��m�[�h�ԍ��i 0�ȏ�̐����l �j
		@return         none
		@exception      none
		*/
		void NodeRender(ShaderBase*, const int id);


		/*
		�L�[�t���[���A�j���[�V�����p
		*/
		void KeyframeAnimationRender(ShaderBase* shader);

		void KeyframeUpdate(std::string, int&);
		void KeyframeUpdate(std::string, bool);

		/*
		@brief          ���e����J�����̃A�h���X�擾�p
		@param[in]      ViewCamera�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void SetCamera(ViewCamera*);


		/*
		@brief          �w��̃m�[�h���D���ȐF�ɐݒ�ł���
		�m�[�h�ԍ����͈͊O�̏ꍇ�͂��ׂĂɑ΂��ĕύX
		@param[in]      rgba
		@param[in]      �ύX�𔽉f�������m�[�h�ԍ��i 0�ȏ�̐����l �j
		@return         none
		@exception      none
		*/
		void SetModelMaterialColor(Color rgba, const int nodeID, eMatrerialType);

		/*
		@brief          �S�Ẵm�[�h���D���ȐF�ɐݒ�ł���
		�m�[�h�ԍ����͈͊O�̏ꍇ�͂��ׂĂɑ΂��ĕύX
		@param[in]      rgba
		@param[in]      �ύX�𔽉f�������m�[�h�ԍ��i 0�ȏ�̐����l �j
		@return         none
		@exception      none
		*/
		void SetModelMaterialColor(Color rgba, eMatrerialType);

		void SetColor(Color);

		/*
		@brief          �w��̃m�[�h�̃e�N�X�`���I�u�W�F�N�g���擾
		@param[in]      �w��m�[�h�ԍ�
		@return         ID3D11ShaderResourceView�^�I�u�W�F�N�g
		@exception      none
		*/
		ID3D11ShaderResourceView* GetTexture(const int id);

		
		/*
		@brief          �S�Ẵm�[�h�ɑ΂��ē����e�N�X�`���I�u�W�F�N�g���擾
		@param          �쐬�������e�N�X�`���摜�̑��΃p�X
		@return         �������Fture/���s��:false
		@exception      none
		*/
		bool SetTexture(Texture*,eMatrerialType);

		/*
		@brief          �w��̃m�[�h�ɑ΂��ē����e�N�X�`�����擾
		@param          �쐬�������e�N�X�`���摜�̑��΃p�X
		@param[in]      �w��m�[�h�ԍ�
		@return         �������Fture/���s��:false
		@exception      none
		*/
		 bool SetNodeTexture(Texture*, const int id, eMatrerialType);

		/*
		@brief          �e�N�X�`���̂���e�f�B���N�g���[�̐ݒ�.�����Ċe�e�N�X�`���̓ǂݍ���
		@param[in]      �f�B���N�g���[���̐ݒ�
		@return         �������Fture/���s��:false
		@exception      none
		*/
		void SetTextureDirectoryName(std::string);

		std::string GetModelPath()const;
		std::string GetAnimationName(const int);
		int GetAnimationListSize()const;

	private:
		/*
		@brief          ��{���̎擾
		@param[in]      Direct3DManager�^�̃A�h���X
		@return         �������Fture/���s��:false
		@exception      none
		*/
		bool LoadModelBuffers(Direct3DManager*);

		
		/*
		@brief          �`�揈��
		@param[in]      Direct3DManager�^�̃A�h���X
		@param[in]      �`�悷��m�[�h�ԍ�
		@return         none
		@exception      none
		*/
		void RenderBuffers(Direct3DManager*, Mesh&);

		/*
		@brief          �V�F�[�_�[�ɓn���p�����[�^�[��ݒ肷��֐��B�h����ŃI�[�o�[���C�h���������L�q
		@param          ���𓾂���ModelMesh�^�|�C���^
		@return         none
		@exception      none
		*/
		void CreateConstantBuffers(Mesh&);



	private:
		ViewCamera* m_camera;
		std::string m_modelPath;
		std::string m_prevAnimationName;
		std::vector<std::string> m_animationNameList;
		std::vector<Mesh> m_nodeMeshBuffer;
		std::unique_ptr<FbxLoader> m_fbxLoader;
	};

}

#endif