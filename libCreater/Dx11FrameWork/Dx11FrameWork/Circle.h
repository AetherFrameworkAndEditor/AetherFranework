#ifndef _CIRCLE_H
#define _CIRCLE_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Circle.h
@brief     円の基本モデル

*******************************************************************************
@date       2016/1/15
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu

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
		@brief          初期化用関数。派生先でオーバーライドし初期化の処理を記述
		@param          none
		@return         none
		@exception      none
		*/
		bool InitializeBuffers()override;

		/*
		@brief          解放用関数。派生先でオーバーライドし解放の処理を記述
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeBuffers()override;

		/*
		@brief          描画用関数。派生先でオーバーライドし描画の処理を記述
		@param          none
		@return         none
		@exception      none
		*/
		void RenderBuffers()override;

	};

}
#endif