/******************************************************************************/
/*! @addtogroup aetherClass
@file      Physics.h
@brief     物理演算系の関数を定義

*******************************************************************************
@date       2015/12/27
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/23 橋本航
-# Initial Version
******************************************************************************/
#ifndef _AETHERPHYSICS_H
#define _AETHERPHYSICS_H
#include <memory>
#include "ModelBase.h"
#include"Sphere.h"
#include"Line.h"
namespace aetherFunction{
	//bool CollideBoxOBB(const std::shared_ptr<aetherClass::ModelBase>&, const std::shared_ptr<aetherClass::ModelBase>&);
	//bool IsCompareLengthOBB(const std::shared_ptr<aetherClass::ModelBase>&, const std::shared_ptr<aetherClass::ModelBase>&, aetherClass::Vector3&, aetherClass::Vector3&);




	/*
	@brief          [使わないでください]
	*/
	static bool IsCompareLengthOBB(aetherClass::ModelBase& modelA, aetherClass::ModelBase& modelB, aetherClass::Vector3& sep, aetherClass::Vector3& distance)
	{
		float length = fabsf(sep.Dot(distance));
		float lenA =
			fabsf(modelA.GetAxis()._axisX.Dot(sep) * (modelA.property._transform._scale._x))
			+ fabsf(modelA.GetAxis()._axisY.Dot(sep) * (modelA.property._transform._scale._y))
			+ fabsf(modelA.GetAxis()._axisZ.Dot(sep) * (modelA.property._transform._scale._z));
		float lenB =
			fabsf(modelB.GetAxis()._axisX.Dot(sep) * (modelB.property._transform._scale._x))
			+ fabsf(modelB.GetAxis()._axisY.Dot(sep) * (modelB.property._transform._scale._y))
			+ fabsf(modelB.GetAxis()._axisZ.Dot(sep) * (modelB.property._transform._scale._z));

		if (length > lenA + lenB)return false;
		return true;
	}


	/*
	@brief          OBBで当たり判定を取る。
	@param[in]      判定を取りたい四角形
	@param[in]      判定を取りたい四角形
	@return         成功時 true/失敗時	false
	@exception      none
	*/
	static bool CollideBoxOBB(aetherClass::ModelBase& modelA, aetherClass::ModelBase& modelB)
	{
		aetherClass::Vector3 distance;
		distance._x = modelA.property._transform._translation._x - modelB.property._transform._translation._x;
		distance._y = modelA.property._transform._translation._y - modelB.property._transform._translation._y;
		distance._z = modelA.property._transform._translation._z - modelB.property._transform._translation._z;

		modelA.GetAxis().Update(modelA.property._transform._rotation);
		modelB.GetAxis().Update(modelB.property._transform._rotation);

		if (!IsCompareLengthOBB(modelA, modelB, modelA.GetAxis()._axisX, distance))return false;
		if (!IsCompareLengthOBB(modelA, modelB, modelA.GetAxis()._axisY, distance))return false;
		if (!IsCompareLengthOBB(modelA, modelB, modelA.GetAxis()._axisZ, distance))return false;

		if (!IsCompareLengthOBB(modelA, modelB, modelB.GetAxis()._axisX, distance))return false;
		if (!IsCompareLengthOBB(modelA, modelB, modelB.GetAxis()._axisY, distance))return false;
		if (!IsCompareLengthOBB(modelA, modelB, modelB.GetAxis()._axisZ, distance))return false;

		aetherClass::Vector3 sep;
		SecureZeroMemory(&sep, sizeof(sep));

		sep = modelA.GetAxis()._axisX.Cross(modelB.GetAxis()._axisX);
		if (!IsCompareLengthOBB(modelA, modelB, sep, distance))return false;
		sep = modelA.GetAxis()._axisX.Cross(modelB.GetAxis()._axisY);
		if (!IsCompareLengthOBB(modelA, modelB, sep, distance))return false;
		sep = modelA.GetAxis()._axisX.Cross(modelB.GetAxis()._axisZ);
		if (!IsCompareLengthOBB(modelA, modelB, sep, distance))return false;

		sep = modelA.GetAxis()._axisY.Cross(modelB.GetAxis()._axisX);
		if (!IsCompareLengthOBB(modelA, modelB, sep, distance))return false;
		sep = modelA.GetAxis()._axisY.Cross(modelB.GetAxis()._axisY);
		if (!IsCompareLengthOBB(modelA, modelB, sep, distance))return false;
		sep = modelA.GetAxis()._axisY.Cross(modelB.GetAxis()._axisZ);
		if (!IsCompareLengthOBB(modelA, modelB, sep, distance))return false;

		sep = modelA.GetAxis()._axisZ.Cross(modelB.GetAxis()._axisX);
		if (!IsCompareLengthOBB(modelA, modelB, sep, distance))return false;
		sep = modelA.GetAxis()._axisZ.Cross(modelB.GetAxis()._axisY);
		if (!IsCompareLengthOBB(modelA, modelB, sep, distance))return false;
		sep = modelA.GetAxis()._axisZ.Cross(modelB.GetAxis()._axisZ);
		if (!IsCompareLengthOBB(modelA, modelB, sep, distance))return false;

		return true;
	}


	/*
	@brief          SphereとRayで当たり判定を取る。
	@param[in]		Sphereだよ〜
	@param[in]      Rayを発射する起点
	@param[in]      Rayの向き
	@return         成功時 true/失敗時	false
	@exception      none
	*/
	static bool RaySphereIntersect(aetherClass::Sphere& sphere, aetherClass::Vector3 rayOrigin, aetherClass::Vector3 rayDirection, float scalar = 1)
	{
		rayDirection *= scalar;

		float Xa = rayOrigin._x - sphere.property._transform._translation._x;
		float Ya = rayOrigin._y - sphere.property._transform._translation._y;
		float Za = rayOrigin._z - sphere.property._transform._translation._z;

		float a = ((rayDirection._x*rayDirection._x) + (rayDirection._y*rayDirection._y) + (rayDirection._z*rayDirection._z));
		float b = 2.0f * ((rayDirection._x * Xa) + (rayDirection._y * Ya) + (rayDirection._z * Za));
		float c = (Xa * Xa) + (Ya*Ya) + (Za*Za) - (sphere.property._transform._scale._x * sphere.property._transform._scale._x);

		float d = b*b - 4.0f * a * c;

		if (d < 0.0f)return false;

		d = sqrt(d);
		float t0 = (-b + d) / (2.0f * a);
		float t1 = (-b - d) / (2.0f * a);

		float t = 2.0f;
		if ((t0 >= 0.0f) && (t0 <= 1.0f) && (t0 < t))t = t0;
		if ((t1 >= 0.0f) && (t1 <= 1.0f) && (t1 < t))t = t1;
		if (t > 1.0f)return false;

		return true;
	}

	/*
	@brief          SphereとRayで当たり判定を取る。
	@param[in]		Ray構造体
	@return         成功時 true/失敗時	false
	@exception      none
	*/
	static bool RaySphereIntersect(aetherClass::Sphere& sphere, aetherClass::RayVector rayVector)
	{
		rayVector._direction *= rayVector._scaler;

		float Xa = rayVector._origin._x - sphere.property._transform._translation._x;
		float Ya = rayVector._origin._y - sphere.property._transform._translation._y;
		float Za = rayVector._origin._z - sphere.property._transform._translation._z;

		float a = ((rayVector._direction._x*rayVector._direction._x) + (rayVector._direction._y*rayVector._direction._y) + (rayVector._direction._z*rayVector._direction._z));
		float b = 2.0f * ((rayVector._direction._x * Xa) + (rayVector._direction._y * Ya) + (rayVector._direction._z * Za));
		float c = (Xa * Xa) + (Ya*Ya) + (Za*Za) - (sphere.property._transform._scale._x * sphere.property._transform._scale._x);

		float d = b*b - 4.0f * a * c;

		if (d < 0.0f)return false;

		d = sqrt(d);
		float t0 = (-b + d) / (2.0f * a);
		float t1 = (-b - d) / (2.0f * a);

		float t = 2.0f;
		if ((t0 >= 0.0f) && (t0 <= 1.0f) && (t0 < t))t = t0;
		if ((t1 >= 0.0f) && (t1 <= 1.0f) && (t1 < t))t = t1;
		if (t > 1.0f)return false;

		return true;
	}


	/*
	@brief          ２点間の距離を計算する。（３次元用）
	@param[in]      １点目
	@param[in]      ２点目
	@return         ２点間の距離
	@exception      none
	*/
	static float Distance3D(aetherClass::Vector3& other1, aetherClass::Vector3& other2)
	{
		aetherClass::Vector3 vector = other2 - other1;
		float distance = vector._x * vector._x + vector._y * vector._y + vector._z * vector._z;
		return distance;
	}

	/*
	@brief          球と球の当たり判定
	@param[in]      当たり判定を取りたい球
	@param[in]      当たり判定を取りたい球
	@return         成功時 true/失敗時	false
	@exception      none
	*/
	static bool ColliderBoxSphere(aetherClass::Sphere& other1, aetherClass::Sphere& other2, aetherClass::Vector3* hitPos = nullptr)
	{
		float distance;
		aetherClass::Vector3
			o1rad = other1.property._transform._scale ,
			o2rad = other2.property._transform._scale ;

		distance = Distance3D(other1.property._transform._translation, other2.property._transform._translation);

		if (distance > (o1rad._x + o2rad._x)*(o1rad._x + o2rad._x))return false;
		if (hitPos){
			float l = (o1rad._x + o2rad._x) - sqrtf(distance);
			aetherClass::Vector3 hit_vec = (other2.property._transform._translation - other1.property._transform._translation).Normalize();
			hit_vec *= l;
			*hitPos = hit_vec;
		}
		return true;
	}


}

#endif