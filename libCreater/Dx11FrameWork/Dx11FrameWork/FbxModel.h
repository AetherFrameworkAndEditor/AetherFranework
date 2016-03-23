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
	private:
		struct Property{
			Transform _transform;
		};
	public:
		 FbxModel::Property property;
	public:
		FbxModel();
		virtual ~FbxModel() = default;

		/*
		@brief          FbxFile�̓ǂݍ��݂Ə�����
		@param[in]      Shader�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		virtual bool LoadFBX(std::string, eAxisSystem)final;

		/*
		@brief          ����p
		@param[in]      Shader�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		virtual void Finalize()final;

		/*
		@brief          �S�Ẵm�[�h�`��p
		@param[in]      Shader�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		virtual void Render(ShaderBase*)final;

		/*
		@brief          �w��m�[�h�̂ݕ`��p�B
		                �͈͊O�̏ꍇ�͂��ׂẴm�[�h��`��
		@param[in]      Shader�I�u�W�F�N�g
		@param[in]      �`�悷��m�[�h�ԍ��i 0�ȏ�̐����l �j
		@return         none
		@exception      none
		*/
		virtual void NodeRender(ShaderBase*, const int id)final;


		/*
			�L�[�t���[���A�j���[�V�����p
		*/
		virtual void KeyFrameAnimation(ShaderBase* shader)final;

		/*
		�L�[�t���[���A�j���[�V�����p
		*/
	//	virtual void SkinAnimation(ShaderBase* shader)final;

		/*
		@brief          ���e����J�����̃A�h���X�擾�p
		@param[in]      ViewCamera�^�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		virtual void SetCamera(ViewCamera*)final;


		/*
		@brief          �w��̃m�[�h���D���ȐF�ɐݒ�ł���
		�m�[�h�ԍ����͈͊O�̏ꍇ�͂��ׂĂɑ΂��ĕύX
		@param[in]      rgba
		@param[in]      �ύX�𔽉f�������m�[�h�ԍ��i 0�ȏ�̐����l �j
		@return         none
		@exception      none
		*/
		virtual void SetModelMaterialColor(Color rgba, const int nodeID, eMatrerialType)final;

		/*
		@brief          �S�Ẵm�[�h���D���ȐF�ɐݒ�ł���
		�m�[�h�ԍ����͈͊O�̏ꍇ�͂��ׂĂɑ΂��ĕύX
		@param[in]      rgba
		@param[in]      �ύX�𔽉f�������m�[�h�ԍ��i 0�ȏ�̐����l �j
		@return         none
		@exception      none
		*/
		virtual void SetModelMaterialColor(Color rgba, eMatrerialType)final;

		/*
		@brief          �w��̃m�[�h�̃e�N�X�`���I�u�W�F�N�g���擾
		@param[in]      �w��m�[�h�ԍ�
		@return         ID3D11ShaderResourceView�^�I�u�W�F�N�g
		@exception      none
		*/
		virtual ID3D11ShaderResourceView* GetTexture(const int id)final;

		
		/*
		@brief          �S�Ẵm�[�h�ɑ΂��ē����e�N�X�`���I�u�W�F�N�g���擾
		@param          �쐬�������e�N�X�`���摜�̑��΃p�X
		@return         �������Fture/���s��:false
		@exception      none
		*/
		virtual bool SetTexture(Texture*,eMatrerialType)final;

		/*
		@brief          �w��̃m�[�h�ɑ΂��ē����e�N�X�`�����擾
		@param          �쐬�������e�N�X�`���摜�̑��΃p�X
		@param[in]      �w��m�[�h�ԍ�
		@return         �������Fture/���s��:false
		@exception      none
		*/
		virtual bool SetNodeTexture(Texture*, const int id, eMatrerialType)final;

		/*
		@brief          �e�N�X�`���̂���e�f�B���N�g���[�̐ݒ�.�����Ċe�e�N�X�`���̓ǂݍ���
		@param[in]      �f�B���N�g���[���̐ݒ�
		@return         �������Fture/���s��:false
		@exception      none
		*/
		virtual void SetTextureDirectoryName(std::string)final;

		virtual std::string GetModelPath()const final;
	protected:

		std::vector<Mesh> m_nodeMeshBuffer;
		std::unique_ptr<FbxLoader> m_fbxLoader;
		

	private:
		/*
		@brief          ��{���̎擾
		@param[in]      Direct3DManager�^�̃A�h���X
		@return         �������Fture/���s��:false
		@exception      none
		*/
		virtual bool LoadModelBuffers(Direct3DManager*)final;

		/*
		@brief          �m�[�h���Ƃɓǂݎ����̋L�q
		@param[in]      Direct3DManager�^�̃A�h���X
		@return         �������Fture/���s��:false
		@exception      none
		*/
		virtual bool LoadNodeMesh(){ return true; }

		/*
		@brief          �`�揈��
		@param[in]      Direct3DManager�^�̃A�h���X
		@param[in]      �`�悷��m�[�h�ԍ�
		@return         none
		@exception      none
		*/
		virtual void RenderBuffers(Direct3DManager*, Mesh)final;

		/*
		@brief          �V�F�[�_�[�ɓn���p�����[�^�[��ݒ肷��֐��B�h����ŃI�[�o�[���C�h���������L�q
		@param          ���𓾂���ModelMesh�^�|�C���^
		@return         none
		@exception      none
		*/
		virtual void CreateConstantBuffers(Mesh);



	private:
		ViewCamera* m_camera;
		std::string m_modelPath;
	};

}

#endif