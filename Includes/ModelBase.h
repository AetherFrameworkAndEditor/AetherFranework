/******************************************************************************/
/*! @addtogroup aetherClass
@file      ModelBase.h
@brief     ���f���N���X�̊��N���X

*******************************************************************************
@date       2016/01/05
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/

#ifndef _MODELBASE_H
#define _MODELBASE_H
#include <string>
#include <memory>

#include "Direct3DManager.h"
#include "DirectXEntity.h"
#include "Axis.h"
#include "Texture.h"
#include"ViewCamera.h"
#include"ShaderBase.h"
#include"Property.h"

namespace aetherClass{
	class ModelBase : 
		public DirectXEntity
	{
	
	public:
		ModelBase();
		virtual ~ModelBase()=default;

		/*
		@brief          �e�N�X�`���̃A�h���X���󂯓n���p�B
		@param[in]      Texture�^�I�u�W�F�N�g
		@return         ������ ture/���s�� false
		@exception      none
		*/
		virtual void SetTexture(Texture*) final;
		
		/*
		@brief          ��������p�֐��B�K���Ă�
		@param[in]      �e�N�X�`���̃p�X��
		@return         ������ ture/���s�� false
		@exception      none
		*/
		virtual void Finalize() final;

		/*
		@brief          �������p�֐��B�K���Ă�
		@param          none
		@return         ������ ture/���s�� false
		@exception      none
		*/
		virtual bool Initialize()final;
		
		/*
		@brief          �`��p�֐��B�K���ĂԁB
		@param[in]      �e�N�X�`���̃p�X��
		@return         none
		@exception      none
		*/
		virtual void Render(ShaderBase*)final;

		/*
		@brief          �`�掞�ɓK�p����J�����̃A�h���X���擾�B���ꂪ�Ă΂�Ȃ��ƁA����ȕ`�悪�ł��Ȃ��B
		@param[in]      ViewCamera�^�̃|�C���^�A�h���X
		@return         none
		@exception      none
		*/
		virtual void SetCamera(ViewCamera*)final;

		/*
		@brief          �C���f�b�N�X���̎擾
		@param[in]      none
		@return         �C���f�b�N�X��
		@exception      none
		*/
		virtual int GetIndexCount()final;


		/*
		@brief          Axis�^�̎Q�Ƃ𓾂�
		@param[in]      none
		@return         Axis�^�ϐ��ւ̎Q��
		@exception      none
		*/
		virtual Axis& GetAxis()final;

		/*
		@brief          オブジェクト名を得る
		@param[in]      none
		@return         オブジェクト名
		@exception      none
		*/
		virtual std::string GetName()const;

	public:
		Property property;
	protected:
		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer, *m_colorBuffer, *m_materialBuffer;;
		unsigned long m_vertexCount, m_indexCount;

		Texture* m_texture;
		ViewCamera* m_camera;

	protected:
		/*
		@brief          ���O�̐ݒ�B�h����ŋL�q
		@param          none
		@return         none
		@exception      none
		*/
		virtual void SetName(const std::string)final;

	private:
	
		/*
		@brief          �������p�֐��B�h����ŃI�[�o�[���C�h���������̏������L�q
		@param          none
		@return         none
		@exception      none
		*/
		virtual bool InitializeBuffers() = 0;

		/*
		@brief          ����p�֐��B�h����ŃI�[�o�[���C�h������̏������L�q
		@param          none
		@return         none
		@exception      none
		*/
		virtual void FinalizeBuffers() = 0;

		/*
		@brief          �`��p�֐��B�h����ŃI�[�o�[���C�h���`��̏������L�q
		@param          none
		@return         none
		@exception      none
		*/
		virtual void RenderBuffers() = 0;

		/*
		@brief          �V�F�[�_�[�ɓn���p�����[�^�[��ݒ肷��֐��B�h����ŃI�[�o�[���C�h���������L�q
		@param          none
		@return         none
		@exception      none
		*/
		virtual void CreateConstantBuffers();

	private:
		Axis m_axis;
		std::string m_modelName;
	
	};
}
#endif