
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Rectangle2D.h
@brief     2Dオブジェクト描画用クラス

*******************************************************************************
@date       2016/1/10
@author     金子和樹
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

