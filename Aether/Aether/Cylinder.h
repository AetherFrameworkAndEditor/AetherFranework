#ifndef _CYLINDER_H
#define _CYLINDER_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Cylinder.h
@brief     円柱の基本モデル

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
	class Cylinder :
		public ModelBase
	{
	private:
		float m_slice;
	public:
		Cylinder();
		Cylinder(float);
		~Cylinder();
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