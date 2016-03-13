#ifndef _TRANSFORM_H
#define _TRANSFORM_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Transform.h
@brief     回転、スケール、トランスレーションを保持するクラス

*******************************************************************************
@date       2015/12/23
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/23		橋本航
-# Initial Version
- 2015/12/26 02:30	金子和樹
-# Add method Transmatrix. 
- 2015/12/26 21:30	金子和樹
-#Delete CopyConstructor.
******************************************************************************/

#include "Vector3.h"
#include<DirectXMath.h>
#include"Matrix4x4.h"

namespace aetherClass{
	class Transform
	{
	public:
		Transform();
		Transform(Vector3, Vector3, Vector3);
		~Transform();

		/*
		@brief          WorldMatixを作る
		@param          none

		@return         作られたWorldMatrix
		@exception      none
		*/
		Matrix4x4 Transmatrix();

	public:
		Vector3 _rotation;
		Vector3 _scale;
		Vector3 _translation;
	};
}
#endif