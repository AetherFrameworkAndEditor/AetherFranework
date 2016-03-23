/******************************************************************************/
/*! @addtogroup aetherClass
@file      Vector4.h
@brief     4�����x�N�g���N���X

*******************************************************************************
@date       2015/12/23
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/


#ifndef _VECTOR4_H
#define _VECTOR4_H
#include "MathUtility.h"
namespace aetherClass{
	class Vector3;
	class Vector4
	{

	public:
		float _x, _y, _z, _w;
	public:
		Vector4();
		Vector4(float, float, float, float);
		Vector4(Vector3);
		Vector4(const Vector4&);
		~Vector4();

		/*
		@brief          �x�N�g���𐳋K������
		@param          none
		@return         none
		@exception      none
		*/
		Vector4 Normalize();

		/*
		@brief          �Ώۃx�N�g���Ƃ̓��ς����߂�
		@param[in]      otherVector
		@return         ���ς̒l��Ԃ�
		@exception      none
		*/
		float Dot(Vector4&);

		/*
		@brief          �Ώۃx�N�g���Ƃ̊O�ς����߂�
		@param[in]      otherVector
		@return         ���ς̒l��Ԃ�
		@exception      none
		*/
		Vector4 Cross(Vector4&);


		/*
		@brief          �l�_�Ԃ̋��������߂�
		@param          none
		@return         �����̒l��Ԃ�
		@exception      none
		*/
		float GetVectorLength();

	public:
		void operator = (Vector4&);
		void operator = (Vector3&);
		void operator = (float);
		
		Vector4 operator + (Vector4);
		void operator += (Vector4);
		Vector4 operator + (float);
		void operator += (float);

		Vector4 operator - (Vector4);
		void operator -= (Vector4);
		Vector4 operator - (float);
		void operator -= (float);


		Vector4 operator * (float);
		void operator *= (float);

		Vector4 operator / (float);
		void  operator /= (float);

		bool  operator == (Vector4);
		bool  operator != (Vector4);
		bool operator < (Vector4);
		bool operator <= (Vector4);
		bool operator > (Vector4);
		bool operator >= (Vector4);
	};
}
#endif