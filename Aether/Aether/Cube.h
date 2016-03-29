#ifndef _CUBE_H
#define _CUBE_H

/******************************************************************************/
/*! @addtogroup aetherClass
@file      Cube.h
@brief     立方体の基本モデル

*******************************************************************************
@date       2016/1/15
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************/
#include "ModelBase.h"
#include"VertexType.h"
namespace aetherClass{
	class Cube :
		public ModelBase
	{
	public:
		Cube();
		~Cube();
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