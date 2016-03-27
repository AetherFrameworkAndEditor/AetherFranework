/******************************************************************************/
/*! @addtogroup aetherClass
@file      SpriteBase.h
@brief     �X�v���C�g�N���X�̊��N���X

*******************************************************************************
@date       2016/01/05
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/

#ifndef _SPRITEBASE_H
#define _SPRITEBASE_H
#include "DirectXEntity.h"
#include "Transform.h"
#include "Axis.h"
#include "Texture.h"
#include"Material.h"
#include"ShaderBase.h"
namespace aetherClass{
	class SpriteBase :
		public DirectXEntity
	{
	private:
		struct Property
		{
			Transform _transform;
			Color _color;
		};
	public:
		SpriteBase();
		virtual ~SpriteBase() = default;


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
		@brief          �C���f�b�N�X���̎擾
		@param[in]      none
		@return         �C���f�b�N�X��
		@exception      none
		*/
		virtual int GetIndexCount()final;

		/*
		@brief          �I�u�W�F�N�g���𓾂�
		@param[in]      none
		@return         �I�u�W�F�N�g��
		@exception      none
		*/
		virtual std::string GetName()final;
		
	private :
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
	public:
		Property property;
	protected:
		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer, *m_colorBuffer;
		unsigned long m_vertexCount, m_indexCount;

		Texture* m_texture;

	protected:

		/*
		@brief          �I�u�W�F�N�g�����w�肷��
		@param[in]      �I�u�W�F�N�g��
		@return         none
		@exception      none
		*/
		virtual void SetName(const std::string);
	private:
		std::string m_spriteName;

	};
}
#endif