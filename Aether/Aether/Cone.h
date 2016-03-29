#ifndef _CONE_H
#define _CONE_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file       Cone.h
@brief     円錐の基本モデル

*******************************************************************************
@date       2016/3/28
@author     金子和樹
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
		@brief          初期化用関数。
		@param          none
		@return         true/false
		@exception      none
		*/
		bool InitializeBuffers()override;

		/*
		@brief          解放用関数。
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeBuffers()override;

		/*
		@brief          描画用関数。
		@param          none
		@return         none
		@exception      none
		*/
		void RenderBuffers()override;

	};
}
#endif
