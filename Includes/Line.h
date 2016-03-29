#ifndef _LINE_H
#define _LINE_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Line.h
@brief     線の基本モデル

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
	struct RayVector
	{
		RayVector(){
			_origin = 0;
			_direction = 0;
			_scaler = 0;
		};
		Vector3 _origin;
		Vector3 _direction;
		float	_scaler;
	};

	class Line :
		public ModelBase
	{
	private:
		RayVector m_rayVector;
	public:
		Line();
		Line(RayVector);
		Line(Vector3, float);
		~Line();
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