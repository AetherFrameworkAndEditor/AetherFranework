#ifndef _POINT_H
#define _POINT_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Point.h
@brief     ���̊�{���f��

*******************************************************************************
@date       2016/1/15
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/
#include "ModelBase.h"
#include"VertexType.h"

namespace aetherClass{
	class Point :
		public ModelBase
	{
	public:
		Point();
		~Point();
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