#ifndef _SKYBOX_H
#define _SKYBOX_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Skybox.h
@brief     �X�J�C�{�b�N�X�̃N���X

*******************************************************************************
@date       2016/2/24
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************/
#include "ModelBase.h"
#include"VertexType.h"

namespace aetherClass{
	class Skybox :
		public ModelBase
	{
	public:
		Skybox();
		~Skybox();
	private:
		/*
		@brief          �������p�֐��B�h����ŃI�[�o�[���C�h���������̏������L�q
		@param          none
		@return         none
		@exception      none
		*/
		bool InitializeBuffers()override;

		/*
		@brief          ����p�֐��B�h����ŃI�[�o�[���C�h������̏������L�q
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeBuffers()override;

		/*
		@brief          �`��p�֐��B�h����ŃI�[�o�[���C�h���`��̏������L�q
		@param          none
		@return         none
		@exception      none
		*/
		void RenderBuffers()override;

		/*
		@brief          �V�F�[�_�[�ɓn���p�����[�^�[��ݒ肷��֐��B�h����ŃI�[�o�[���C�h���������L�q
		@param          none
		@return         none
		@exception      none
		*/
		void CreateConstantBuffers()override;
		ID3D11SamplerState *m_samplerState;
	};

}
#endif