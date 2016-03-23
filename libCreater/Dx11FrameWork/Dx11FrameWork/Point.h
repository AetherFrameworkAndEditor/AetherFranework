#ifndef _POINT_H
#define _POINT_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Point.h
@brief     線の基本モデル

*******************************************************************************
@date       2016/1/15
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/1/15 11:23 金子和樹
-# Initial Version

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