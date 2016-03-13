/******************************************************************************/
/*! @addtogroup aetherClass
@file      Vector4.h
@brief     4次元ベクトルクラス

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
		@brief          ベクトルを正規化する
		@param          none
		@par            Refer
		- 使用するメンバ関数   GetVectorLength
		@par            Modify
		- 変更するメンバ変数   _x
		- 変更するメンバ変数   _y
		- 変更するメンバ変数   _z
		@return         none
		@exception      none
		*/
		Vector4 Normalize();

		/*
		@brief          対象ベクトルとの内積を求める
		@param[in]      otherVector
		@par            Refer
		- 使用するメンバ関数   _x
		- 使用するメンバ関数   _y
		- 使用するメンバ関数   _z
		@par            Modify
		- 変更するメンバ変数   none
		@return         内積の値を返す
		@exception      none
		*/
		float Dot(Vector4&);

		/*
		@brief          対象ベクトルとの外積を求める
		@param[in]      otherVector
		@par            Refer
		- 使用するメンバ関数   _x
		- 使用するメンバ関数   _y
		- 使用するメンバ関数   _z
		@par            Modify
		- 変更するメンバ変数   none
		@return         内積の値を返す
		@exception      none
		*/
		Vector4 Cross(Vector4&);


		/*
		@brief          四点間の距離を求める
		@param          none
		@par            Refer
		- 使用するメンバ関数   _x
		- 使用するメンバ関数   _y
		- 使用するメンバ関数   _z
		@par            Modify
		- 変更するメンバ変数   none
		@return         距離の値を返す
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