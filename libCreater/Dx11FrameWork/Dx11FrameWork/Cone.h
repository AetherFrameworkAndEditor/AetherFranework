#ifndef _CONE_H
#define _CONE_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file       Cone.h
@brief     �~���̊�{���f��

*******************************************************************************
@date       2016/3/28
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/

#include "ModelBase.h"
namespace aetherClass{
class Cone :
	public ModelBase
	{
	public:
		Cone();
		Cone(float);
		~Cone();
	private:
		float m_slice;
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
