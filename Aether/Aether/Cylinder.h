#ifndef _CYLINDER_H
#define _CYLINDER_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Cylinder.h
@brief     �~���̊�{���f��

*******************************************************************************
@date       2016/1/12
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#include "ModelBase.h"
#include"VertexType.h"

namespace aetherClass{
	class Cylinder :
		public ModelBase
	{
	private:
		float m_slice;
	public:
		Cylinder();
		Cylinder(float);
		~Cylinder();
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