#ifndef _LIGHTSHADER_H
#define _LIGHTSHADER_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      LightShader.h
@brief     ���C�g�������V�F�[�_�[�N���X

*******************************************************************************
@date       2016/1/19
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/

#include "ShaderBase.h"
#include"ModelUtility.h"
#include"Light.h"

namespace aetherClass{
	class LightShader :
		public ShaderBase
	{
	public:
		LightShader();
		~LightShader();

		/*
		@brief          ���C�g��ݒ肷��
		@param          ���C�g�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void SetLight(Light*);
	private:
		/*
		@brief          �������p�֐�
		@param          none
		@return         true/false
		@exception      none
		*/
		bool InitializeShader()override;
		/*
		@brief          �I���p�֐�
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeShader()override;
		/*
		@brief          �`�掞�p�֐�
		@param          none
		@return         true/false
		@exception      none
		*/
		bool SetConstantBuffer()override;

		ID3D11Buffer* m_lightBuffer;
		Light *m_light;
	};
}

#endif