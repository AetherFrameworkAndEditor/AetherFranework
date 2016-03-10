#ifndef _QUATERNION_H
#define _QUATERNION_H
#include "Vector3.h"
#include "Matrix4x4.h"
namespace aetherClass{
	class Quaternion
	{

	public:
		float _x, _y, _z, _w;

		static const Quaternion _identity; // 単位クォータニオン
	public:
		Quaternion();

		/*
		@brief          指定要素で初期化
		@param[in]      x成分
		@param[in]      y成分
		@param[in]      z成分
		@param[in]      w成分
		@return         none
		@exception      none
		*/
		Quaternion(const float x,const float y,const float z,const float w);

		/*
		@brief          回転軸と回転角度を指定して初期化
		@param[in]      回転軸
		@param[in]      角度
		@return         none
		@exception      none
		*/
		Quaternion(const Vector3,const float radian);

		~Quaternion();

	public:

		/*
		@brief          各要素に値を設定
		@param[in]      x成分
		@param[in]      y成分
		@param[in]      z成分
		@param[in]      w成分
		@return         none
		@exception      none
		*/
		void SetElement(const float x, const float y, const float z, const float w);

		/*
		@brief          このクォータニオンの長さを返す
		@param[in]      none
		@return         長さ
		@exception      none
		*/
		float GetLength()const;

		/*
		@brief          このクォータニオンの長さの二乗を返す
		@param[in]      none
		@return         長さの二乗
		@exception      none
		*/
		float GetLengthSquared()const;

		/*
		@brief          このクォータニオンを正規化する
		@param[in]      none
		@return         none
		@exception      none
		*/
		Quaternion Normalize();

		/*
		@brief          このクォータニオンが単位クォータニオンであるかの判定
		@param[in]      none
		@return         単位クォータニオンである： true/ 単位クォータニオンではない： false 
		@exception      none
		*/
		bool isIdentity();

		/*
		@brief          引数のクォータニオンとの乗算を行う
		@param[in]      乗算するクォータニオン 
		@return         none
		@exception      none
		*/
		Quaternion Multiply(const Quaternion&);

		/*
		@brief          このクォータニオンをX軸で回転する
		@param[in]      回転する角度
		@return         none
		@exception      none
		*/
		void RotationByX(const float);

		/*
		@brief          このクォータニオンをY軸で回転する
		@param[in]      回転する角度
		@return         none
		@exception      none
		*/
		void RotationByY(const float);

		/*
		@brief          このクォータニオンをZ軸で回転する
		@param[in]      回転する角度
		@return         none
		@exception      none
		*/
		void RotationByZ(const float);

		
		/*
		@brief          このクォータニオンをもとに回転行列を作成
		@param[in]      none
		@return         none
		@exception      none
		*/
		Matrix4x4 Matrix4x4FromQuaternion();
	};
}
#endif