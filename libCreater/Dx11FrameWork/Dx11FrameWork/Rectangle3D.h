#ifndef _RECTANGLE3D_H
#define _RECTANGLE3D_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Rectangle3D.h
@brief     �l�p�`�̊�{���f��

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
	class Rectangle3D :
		public ModelBase
	{
	public:
		Rectangle3D();
		~Rectangle3D();

		void VertexData();


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

		void ReadVertexData();
		VertexType *vertex;

	};

}
#endif