#ifndef _TRANSFORM_H
#define _TRANSFORM_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Transform.h
@brief     ��]�A�X�P�[���A�g�����X���[�V������ێ�����N���X

*******************************************************************************
@date       2015/12/23
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/23		���{�q
-# Initial Version
- 2015/12/26 02:30	���q�a��
-# Add method Transmatrix. 
- 2015/12/26 21:30	���q�a��
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
		@brief          WorldMatix�����
		@param          none

		@return         ���ꂽWorldMatrix
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