#ifndef _CIRCLE_H
#define _CIRCLE_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Circle.h
@brief     �~�̊�{���f��

*******************************************************************************
@date       2016/1/15 11:23
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/1/15 11:23 ���q�a��
-# Initial Version

******************************************************************************/
#include "ModelBase.h"
#include"VertexType.h"

namespace aetherClass{
	class Circle :
		public ModelBase
	{
	private:
		float m_slice;
	public:
		Circle();
		Circle(float);
		~Circle();
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