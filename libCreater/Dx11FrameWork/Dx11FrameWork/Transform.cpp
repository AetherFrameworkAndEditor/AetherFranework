/******************************************************************************/
/*! @addtogroup aetherClass
@file      Transform.cpp
@brief     回転、スケール、トランスレーションを保持するクラス

*******************************************************************************
@date       2015/12/23
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#include"MathUtility.h"
#include "Transform.h"
#include<stddef.h>

using namespace aetherClass;
using namespace DirectX;

	Transform::Transform()
	{
		_translation = NULL;
		_rotation = NULL;
		_scale = 1.0f;
	}
	Transform::Transform(Vector3 translation, Vector3 rotation, Vector3 scale){
		_translation = translation;
		_rotation = rotation;
		_scale = scale;
	}

	Transform::~Transform()
	{
		_translation = NULL;
		_rotation = NULL;
		_scale = 1.0f;
	}

	Matrix4x4 Transform::Transmatrix(){
		Matrix4x4 transmatrix, rotematrix, scalimatrix;
		float pitch, yaw, roll;
		transmatrix.TranslateMatrix(Vector3(_translation._x, _translation._y, _translation._z));
		pitch = _rotation._x	* kAetherRadian;
		yaw = _rotation._y	* kAetherRadian;
		roll = _rotation._z	* kAetherRadian;

		rotematrix.PitchYawRoll(Vector3(pitch, yaw, roll));
		scalimatrix.ScaliMatrix(Vector3(_scale._x, _scale._y, _scale._z));

		Matrix4x4 identity;
		identity= (scalimatrix.Multiply(rotematrix)).Multiply(transmatrix);
		return identity;
	}

