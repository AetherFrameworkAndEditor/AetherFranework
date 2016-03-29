/******************************************************************************/
/*! @addtogroup aetherClass
@file      Transform.cpp
@brief     ��]�A�X�P�[���A�g�����X���[�V������ێ�����N���X

*******************************************************************************
@date       2015/12/23
@author     ���{�q
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
		_position = 0;
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
		Matrix4x4 transmatrix, posmatrix, rotematrix, scalimatrix;


		rotematrix.PitchYawRoll(_rotation*kAetherRadian);
		posmatrix.TranslateMatrix(_position);
		transmatrix.TranslateMatrix(_translation);
		scalimatrix.ScaliMatrix(_scale);

		Matrix4x4 identity = scalimatrix;
		identity = identity.Multiply(posmatrix);
		identity = identity.Multiply(rotematrix);
		identity = identity.Multiply(transmatrix);
		return identity;
	}

