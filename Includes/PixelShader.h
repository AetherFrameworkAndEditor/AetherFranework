#ifndef _PIXELSHADER_H
#define _PIXELSHADER_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      PixelShader.h
@brief     ��{�I�ȃV�F�[�_�[�B���Ɋ��蓖�Ă�ꂽ���������Ƃ��ɁB

*******************************************************************************
@date       2016/1/10
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/

#include "ShaderBase.h"
namespace aetherClass{
	class  PixelShader :
		public ShaderBase
	{

	
	public:
		PixelShader();
		~PixelShader() = default;

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
	};


}

#endif