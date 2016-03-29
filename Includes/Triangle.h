#ifndef _TRIANGLE_H
#define _TRIANGLE_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Triangle.h
@brief     �O�p�`�̊�{���f��

*******************************************************************************
@date       2016/1/9
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/

#include "ModelBase.h"
#include"VertexType.h"
namespace aetherClass{
	class Triangle :
	public ModelBase
	{
	public:
		Triangle();
		~Triangle();
	private:
		/*
		@brief          �������p�֐��B
		@param          none
		@return         true/false
		@exception      none
		*/
		bool InitializeBuffers()override;

		/*
		@brief          ����p�֐��B
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeBuffers()override;

		/*
		@brief          �`��p�֐��B
		@param          none
		@return         none
		@exception      none
		*/
		void RenderBuffers()override;

	};

}

#endif