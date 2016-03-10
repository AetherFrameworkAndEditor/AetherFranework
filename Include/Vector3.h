/******************************************************************************/
/*! @addtogroup aetherClass
@file      Vector3.h
@brief     3�����x�N�g���N���X

*******************************************************************************
@date       2015/12/23
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/23 ���{�q
-# Initial Version
- 2016/1/6 23:00	���q�a��
-# Add TransformCoord.
******************************************************************************/


#ifndef _VECTOR3_H
#define _VECTOR3_H
#include <DirectXMath.h>

namespace aetherClass{
	class Matrix4x4;
	class Vector3
	{
	public:
		Vector3();
		Vector3(float x, float y, float z);
		~Vector3();

		/*
		@brief          �x�N�g���𐳋K������
		@param          none
		@return         none
		@exception      none
		*/
		Vector3 Normalize();

		/*
		@brief          �Ώۃx�N�g���Ƃ̓��ς����߂�
		@param[in]      otherVector
		@return         ���ς̒l��Ԃ�
		@exception      none
		*/
		float Dot(Vector3&);

		/*
		@brief          �Ώۃx�N�g���Ƃ̊O�ς����߂�
		@param[in]      otherVector
		@return         ���ς̒l��Ԃ�
		@exception      none
		*/
		Vector3 Cross(Vector3&);

		/*
		@brief          �O�_�Ԃ̋��������߂�
		@param          none
		@return         �����̒l��Ԃ�
		@exception      none
		*/
		float GetVectorLength();

		/*
		@brief          �Ώۍs��Ō��݂̃x�N�g����ϊ�
		@param          none
		@return			none
		@exception      none
		*/
		Vector3 TransformCoord(Matrix4x4 matrix);
	public:

		float _x, _y, _z;

	public:
		void operator =(float);

		Vector3 operator + (Vector3);
		void operator += (Vector3);
		Vector3 operator + (float);
		void operator += (float);

		Vector3 operator - (Vector3);
		void operator -= (Vector3);
		Vector3 operator - (float);
		void operator -= (float);

		Vector3 operator * (float);

		void operator *= (float);

		Vector3 operator / (float);
		void  operator /= (float);

		bool  operator == (Vector3);
		bool  operator != (Vector3);
		bool operator < (Vector3);
		bool operator <= (Vector3);
		bool operator > (Vector3);
		bool operator >= (Vector3);


	};
}
#endif