#ifndef _RECTANGLE3D_H
#define _RECTANGLE3D_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Rectangle3D.h
@brief     四角形の基本モデル

*******************************************************************************
@date       2016/1/12
@author     金子和樹
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

		void ReadVertexData();
		VertexType *vertex;

	};

}
#endif