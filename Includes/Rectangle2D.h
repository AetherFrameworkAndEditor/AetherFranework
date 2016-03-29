
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Rectangle2D.h
@brief     2D�I�u�W�F�N�g�`��p�N���X

*******************************************************************************
@date       2016/1/10
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _RECTANGLE2D_H
#define _RECTANGLE2D_H

#include"SpriteBase.h"

namespace aetherClass{
	class Rectangle2D : public SpriteBase
	{
	public:
		Rectangle2D();
		~Rectangle2D() = default;

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

	};
}
#endif

