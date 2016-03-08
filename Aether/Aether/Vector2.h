/******************************************************************************/
/*! @addtogroup aetherClass
@file      Vector2.h
@brief     2次元ベクトルクラス

*******************************************************************************
@date       2015/12/23
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/23 橋本航
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
		@brief          ベクトルを正規化する
		@param          none
		@return         none
		@exception      none
		*/
		Vector2 Normalize();

		/*
		@brief          対象ベクトルとの内積を求める
		@param[in]      otherVector
		@return         内積の値を返す
		@exception      none
		*/
		float Dot(Vector2& otherVector);

		/*
		@brief          二点間の距離を求める
		@param          none
		@return         距離の値を返す
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
