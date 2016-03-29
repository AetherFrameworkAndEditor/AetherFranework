#ifndef _VIEWCAMERA_H
#define _VIEWCAMERA_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      ViewCamera.h
@brief     カメラのクラス

*******************************************************************************
@date       2016/1/7
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/
#define DEBUG_MODE
#include "Vector3.h"
#include"Matrix4x4.h"
#include "Direct3DManager.h"
namespace aetherClass{
	class ViewCamera
	{
	public:
		struct Property{
			Vector3 _translation;
			Vector3 _rotation;
			Vector3 _lookUp;
			Vector3 _lookAt;
		};
	public:
		ViewCamera();
		~ViewCamera() = default;

		Property property;

		/*
		@brief          ビュー行列を生成する
		@param[in]      none
		@return         none
		@exception      none
		*/
		void Render();
		/*
		@brief          ビュー行列を取得する
		@param[in]      none
		@return         ビュー行列
		@exception      none
		*/
		Matrix4x4 GetViewMatrix();
#ifdef DEBUG_MODE
		/*
		@brief          カメラコントロールを呼ぶ
		@param[in]      none
		@return         none
		@exception      DEBUG_MODEが定義されていれば使用可能
		*/
		void Controller();
#endif

	private:
		Matrix4x4 m_viewMatrix;
	};


}

#endif