/******************************************************************************/
/*! @addtogroup aetherClass
@file      Vector2.h
@brief     2�����x�N�g���N���X

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
******************************************************************************/


#ifndef _VECTOR2_H
#define _VECTOR2_H

#include <DirectXMath.h>
namespace aetherClass{
	class Vector2
	{
	public:
		float _x, _y;
	public:
		Vector2();
		Vector2(float, float);
		~Vector2();

		/*
		@brief          �x�N�g���𐳋K������
		@param          none
		@return         none
		@exception      none
		*/
		Vector2 Normalize();

		/*
		@brief          �Ώۃx�N�g���Ƃ̓��ς����߂�
		@param[in]      otherVector
		@return         ���ς̒l��Ԃ�
		@exception      none
		*/
		float Dot(Vector2& otherVector);

		/*
		@brief          ��_�Ԃ̋��������߂�
		@param          none
		@return         �����̒l��Ԃ�
		@exception      none
		*/
		float GetVectorLength();

	public:
		void operator = (float input);

		Vector2 operator + (Vector2 input);
		void operator += (Vector2 input);
		Vector2 operator + (float input);
		void operator += (float input);

		Vector2 operator - (Vector2 input);
		void operator -= (Vector2 input);
		Vector2 operator - (float input);
		void operator -= (float input);


		Vector2 operator * (float input);
		void operator *= (float input);

		Vector2 operator / (float input);
		void  operator /= (float input);

		bool  operator == (Vector2 input);
		bool  operator != (Vector2 input);
		bool operator < (Vector2 input);
		bool operator <= (Vector2 input);
		bool operator > (Vector2 input);
		bool operator >= (Vector2 input);
	};
}
#endif
