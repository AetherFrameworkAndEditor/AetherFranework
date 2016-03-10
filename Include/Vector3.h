/******************************************************************************/
/*! @addtogroup aetherClass
@file      Vector3.h
@brief     3次元ベクトルクラス

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
- 2016/1/6 23:00	金子和樹
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
		@brief          ベクトルを正規化する
		@param          none
		@return         none
		@exception      none
		*/
		Vector3 Normalize();

		/*
		@brief          対象ベクトルとの内積を求める
		@param[in]      otherVector
		@return         内積の値を返す
		@exception      none
		*/
		float Dot(Vector3&);

		/*
		@brief          対象ベクトルとの外積を求める
		@param[in]      otherVector
		@return         内積の値を返す
		@exception      none
		*/
		Vector3 Cross(Vector3&);

		/*
		@brief          三点間の距離を求める
		@param          none
		@return         距離の値を返す
		@exception      none
		*/
		float GetVectorLength();

		/*
		@brief          対象行列で現在のベクトルを変換
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