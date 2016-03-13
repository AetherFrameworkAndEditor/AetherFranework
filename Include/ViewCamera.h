#ifndef _VIEWCAMERA_H
#define _VIEWCAMERA_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      ViewCamera.h
@brief     カメラのクラス

*******************************************************************************
@date       2016/1/7 4:23
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/1/7 4:23 金子和樹
-# Initial Version

******************************************************************************/
#define DEBUG_MODE
#include "Vector3.h"
#include"Matrix4x4.h"
#include "Direct3DManager.h"
namespace aetherClass{
	class ViewCamera
	{
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


		void Render();
		Matrix4x4 GetViewMatrix();
#ifdef DEBUG_MODE
		void Controller();
#endif

	private:
		Matrix4x4 m_viewMatrix;
	};


}

#endif