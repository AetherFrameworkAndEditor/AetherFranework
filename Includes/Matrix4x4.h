#ifndef _MATRIX4X4_H
#define _MATRIX4X4_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Matrix4x4.h
@brief     4x4の行列クラス

*******************************************************************************
@date       2016/1/6
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/

#include<DirectXMath.h>
#include"Vector3.h"
#include"Vector4.h"

namespace aetherClass{
	class Matrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4(const float* arr,unsigned int arraysize);
		Matrix4x4(
			float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44	);
		~Matrix4x4();
		
		/*
		@brief          この行列を単位行列にする
		@param          none

		@return         none
		@exception      none
		*/
		void Identity();


		/*
		@brief          この行列を単位行列で、3行3列めだけマイナス値にする。
		                この行列を掛け合わせることで右手系を左手系に変換できる
		@param          none

		@return         none
		@exception      none
		*/
		void RightToLeftIdentity();


		/*
		@brief          この行列を逆行列にする
		@param          none

		@return         none
		@exception      none
		*/
		void Inverse();

		/*
		@brief          この行列を転置行列にする
		@param          none

		@return         none
		@exception      none
		*/
		void Transpose();

		/*
		@brief          この行列を移動行列にする
		@param			xyzの移動要素

		@return         none
		@exception      none
		*/
		void TranslateMatrix(Vector3 translate);

		/*
		@brief          この行列を拡大縮小行列にする
		@param			xyzの要素

		@return         none
		@exception      none
		*/
		void ScaliMatrix(Vector3 scaling);

		/*
		@brief          この行列をＸ軸回りの回転行列にする
		@param			角度（radian）

		@return         none
		@exception      none
		*/
		void RotationAxisX(float rotation);

		/*
		@brief          この行列をＹ軸回りの回転行列にする
		@param			角度（radian）

		@return         none
		@exception      none
		*/
		void RotationAxisY(float rotation);

		/*
		@brief          この行列をＺ軸回りの回転行列にする
		@param			角度（radian）

		@return         none
		@exception      none
		*/
		void RotationAxisZ(float rotation);

		/*
		@brief          この行列をEuler角系の回転行列にする
		@param			角度（radian）x,y,z

		@return         none
		@exception      none
		*/
		void RotationMatrix(Vector3 rotation);

		/*
		@brief          この行列をYawPitchRollの回転行列にする
		@param			角度（radian）x,y,z

		@return         none
		@exception      none
		*/
		void PitchYawRoll(Vector3 rotation);

		/*
		@brief          この行列を別の行列と掛け合わせる
		@param			掛け合わせる行列

		@return         掛け合わされた行列
		@exception      none
		*/
		Matrix4x4 Multiply(Matrix4x4 matrix);


		/*
		@brief          左手系のスクリーン変換行列　視野角を利用
		@param			視野角
		@param			アスペクト比
		@param			近クリップ面の距離
		@param			遠クリップ面の距離

		@return         none
		@exception      none
		*/
		void PerspectiveFovLH(float fov, float aspect, float zNear, float zFar);
		/*
		@brief          右手系のスクリーン変換行列　視野角を利用
		@param			視野角
		@param			アスペクト比
		@param			近クリップ面の距離
		@param			遠クリップ面の距離

		@return         none
		@exception      none
		*/
		void PerspectiveFovRH(float fov, float aspect, float zNear, float zFar);
		
		/*
		@brief          左手系のスクリーン変換行列　近クリップ面の幅を利用
		@param			幅
		@param			高さ
		@param			近クリップ面の距離
		@param			遠クリップ面の距離

		@return         none
		@exception      none
		*/
		void PerspectiveLH(float width,float height,float zNear, float zFar);
		/*
		@brief          右手系のスクリーン変換行列　近クリップ面の幅を利用
		@param			幅
		@param			高さ
		@param			近クリップ面の距離
		@param			遠クリップ面の距離

		@return         none
		@exception      none
		*/
		void PerspectiveRH(float width, float height, float zNear, float zFar);

		/*
		@brief          左手系のスクリーン変換行列　zを利用せず大きさをそのまま表現できる
		@param			幅
		@param			高さ
		@param			近クリップ面の距離
		@param			遠クリップ面の距離

		@return         none
		@exception      none
		*/
		void OrthoLH(float width, float height, float zNear, float zFar);
		/*
		@brief          右手系のスクリーン変換行列　zを利用せず大きさをそのまま表現できる
		@param			幅
		@param			高さ
		@param			近クリップ面の距離
		@param			遠クリップ面の距離

		@return         none
		@exception      none
		*/
		void OrthoRH(float width, float height, float zNear, float zFar);
	
		/*
		@brief          左手系のビュー変換行列
		@param			位置
		@param			注視点
		@param			カメラの上方向

		@return         none
		@exception      none
		*/
		void LookAtLH(Vector3 pos, Vector3 lookat, Vector3 up);

		public:
		union{
			struct{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float _matrix[4][4];
		};
	public:
		Matrix4x4 operator +();
		Matrix4x4 operator -();

		Matrix4x4 operator +(Matrix4x4);
		Matrix4x4 operator -(Matrix4x4);
		Matrix4x4 operator *(Matrix4x4);
		Vector4 operator *(Vector4);
		Vector3 operator *(Vector3);

		Matrix4x4 operator +(float);
		Matrix4x4 operator -(float);
		Matrix4x4 operator *(float);
		Matrix4x4 operator /(float);

		void operator +=(Matrix4x4);
		void operator -=(Matrix4x4);
		void operator *=(Matrix4x4);

		void operator +=(float);
		void operator -=(float);
		void operator *=(float);
		void operator /=(float);

	};
};
#endif