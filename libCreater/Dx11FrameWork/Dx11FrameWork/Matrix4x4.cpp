/******************************************************************************/
/*! @addtogroup aetherClass
@file      Matrix4x4.h
@brief     4x4‚Ìs—ñƒNƒ‰ƒX

*******************************************************************************
@date       2016/1/6 17:10
@author     ‹àq˜a÷
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/1/6 17:10	‹àq˜a÷
-# Initial Version
- 2016/1/6 21:45	‹àq˜a÷
-# Add View relation methods

******************************************************************************/
#include"Matrix4x4.h"
#include<stddef.h>
#include<string>


using namespace aetherClass;

Matrix4x4::Matrix4x4(){
	memset(&_matrix, NULL,sizeof(_matrix));
}
Matrix4x4::~Matrix4x4(){
	memset(&_matrix, NULL, sizeof(_matrix));
}

Matrix4x4::Matrix4x4(
	float _11, float _12, float _13, float _14,
	float _21, float _22, float _23, float _24,
	float _31, float _32, float _33, float _34,
	float _41, float _42, float _43, float _44)
{
		this->_11 = _11, this->_12 = _12, this->_13 = _13, this->_14 = _14,
		this->_21 = _21, this->_22 = _22, this->_23 = _23, this->_24 = _24,
		this->_31 = _31, this->_32 = _32, this->_33 = _33, this->_34 = _34,
		this->_41 = _41, this->_42 = _42, this->_43 = _43, this->_44 = _44;
}

Matrix4x4::Matrix4x4(const float* array, unsigned int size){
	memset(&_matrix, NULL, sizeof(_matrix));
	if (size > 16)return;
	memcpy(&_matrix, array, sizeof(float)*size);
}


void Matrix4x4::TranslateMatrix(Vector3 in){
	this->Identity();
	_41 = in._x; _42 = in._y; _43 = in._z;
}

void Matrix4x4::ScaliMatrix(Vector3 in){
	this->Identity();
	_11 = in._x; _22 = in._y; _33 = in._z;
}

void Matrix4x4::RotationAxisX(float in){
	this->Identity();
	_22 = cosf(in); _23 = -sinf(in);
	_32 = sinf(in); _33 = cosf(in);
}
void Matrix4x4::RotationAxisY(float in){
	this->Identity();
	_11 = cosf(in); _13 = sinf(in);
	_31 = -sinf(in); _33 = cosf(in);

}
void Matrix4x4::RotationAxisZ(float in){
	this->Identity();
	_11 = cosf(in); _12 = -sinf(in);
	_21 = sinf(in); _22 = cosf(in);
}

void Matrix4x4::RotationMatrix(Vector3 in){
	this->Identity();
	_11 = cosf(in._x)*cosf(in._y)*cosf(in._z) - sinf(in._x)*sinf(in._z); _12 = -(cosf(in._x)*cosf(in._y)*sinf(in._z) - sinf(in._x)*cosf(in._z)); _13 = cosf(in._x)*sinf(in._y);
	_21 = sinf(in._x)*cosf(in._y)*cosf(in._z) + cosf(in._x)*sinf(in._z); _22 = -(sinf(in._x)*cosf(in._y)*sinf(in._z) + cosf(in._x)*cosf(in._z));  _23 = sinf(in._x)*sinf(in._y);
	_31 = -(sinf(in._y)*cosf(in._z)); _32 = sinf(in._y)*sinf(in._z); _33 = cosf(in._y);
}
void Matrix4x4::PitchYawRoll(Vector3 in){
	this->Identity();

	float halfRoll = in._z*0.5f;
	float sinR = sin(halfRoll), cosR = cos(halfRoll);

	float halfPitch = in._x*0.5f;
	float sinP = sin(halfPitch), cosP = cos(halfPitch);

	float halfYaw = in._y*0.5f;
	float sinY = sin(halfYaw), cosY = cos(halfYaw);

	float qX = (cosY*sinP*cosR) + (sinY*cosP*sinR);
	float qY = (sinY*cosP*cosR) - (cosY*sinP*sinR);
	float qZ = (cosY*cosP*sinR) - (sinY*sinP*cosR);
	float qW = (cosY*cosP*cosR) + (sinY*sinP*sinR);

	float xx = qX * qX;
	float yy = qY * qY;
	float zz = qZ * qZ;
	float xy = qX * qY;
	float zw = qZ * qW;
	float zx = qZ * qX;
	float yw = qY * qW;
	float yz = qY * qZ;
	float xw = qX * qW;

	_11 = 1.0f - (2.0f * (yy + zz));
	_12 = 2.0f * (xy + zw);
	_13 = 2.0f * (zx - yw);
	_14 = 0.0f;

	_21 = 2.0f * (xy - zw);
	_22 = 1.0f - (2.0f * (zz + xx));
	_23 = 2.0f * (yz + xw);
	_24 = 0.0f;

	_31 = 2.0f * (zx + yw);
	_32 = 2.0f * (yz - xw);
	_33 = 1.0f - (2.0f * (yy + xx));
	_34 = 0.0f;

}



void Matrix4x4::Identity(){
	memset(&_matrix, 0, sizeof(_matrix));
	_matrix[0][0] = _matrix[1][1] = _matrix[2][2] = _matrix[3][3] = 1;
}

//
void Matrix4x4::RightToLeftIdentity(){
	memset(&_matrix, 0, sizeof(_matrix));
	_matrix[0][0] = _matrix[1][1] = _matrix[2][2] = 1;
	_matrix[3][3] = -1;

	return;
}

void Matrix4x4::Transpose(){
	Matrix4x4 out;
	out._11 = _11; out._12 = _21; out._13 = _31; out._14 = _41;
	out._21 = _12; out._22 = _22; out._23 = _32; out._24 = _42;
	out._31 = _13; out._32 = _23; out._33 = _33; out._34 = _43;
	out._41 = _14; out._42 = _24; out._43 = _34; out._44 = _44;
	*this = out;
}


void Matrix4x4::Inverse(){
	float det;
	det = (_matrix[0][0] * _matrix[1][1] * _matrix[2][2] * _matrix[3][3]) + (_matrix[0][0] * _matrix[1][2] * _matrix[2][3] * _matrix[3][1]) + (_matrix[0][0] * _matrix[1][3] * _matrix[2][1] * _matrix[3][2])
		+ (_matrix[0][1] * _matrix[1][0] * _matrix[2][3] * _matrix[3][2]) + (_matrix[0][1] * _matrix[1][2] * _matrix[2][0] * _matrix[3][3]) + (_matrix[0][1] * _matrix[1][3] * _matrix[2][2] * _matrix[3][0])
		+ (_matrix[0][2] * _matrix[1][0] * _matrix[2][1] * _matrix[3][3]) + (_matrix[0][2] * _matrix[1][1] * _matrix[2][3] * _matrix[3][0]) + (_matrix[0][2] * _matrix[1][3] * _matrix[2][0] * _matrix[3][1])
		+ (_matrix[0][3] * _matrix[1][0] * _matrix[2][2] * _matrix[3][1]) + (_matrix[0][3] * _matrix[1][1] * _matrix[2][0] * _matrix[3][2]) + (_matrix[0][3] * _matrix[1][2] * _matrix[2][1] * _matrix[3][0])
		- (_matrix[0][0] * _matrix[1][1] * _matrix[2][3] * _matrix[3][2]) - (_matrix[0][0] * _matrix[1][2] * _matrix[2][1] * _matrix[3][3]) - (_matrix[0][0] * _matrix[1][3] * _matrix[2][2] * _matrix[3][1])
		- (_matrix[0][1] * _matrix[1][0] * _matrix[2][2] * _matrix[3][3]) - (_matrix[0][1] * _matrix[1][2] * _matrix[2][3] * _matrix[3][0]) - (_matrix[0][1] * _matrix[1][3] * _matrix[2][0] * _matrix[3][2])
		- (_matrix[0][2] * _matrix[1][0] * _matrix[2][3] * _matrix[3][1]) - (_matrix[0][2] * _matrix[1][1] * _matrix[2][0] * _matrix[3][3]) - (_matrix[0][2] * _matrix[1][3] * _matrix[2][1] * _matrix[3][0])
		- (_matrix[0][3] * _matrix[1][0] * _matrix[2][1] * _matrix[3][2]) - (_matrix[0][3] * _matrix[1][1] * _matrix[2][2] * _matrix[3][0]) - (_matrix[0][3] * _matrix[1][2] * _matrix[2][0] * _matrix[3][1]);
	if (det == 0.0f) return;
	det = 1.0f / det;

	Matrix4x4 inverse;
	inverse._11 = det*(_matrix[1][1] * _matrix[2][2] * _matrix[3][3] + _matrix[1][2] * _matrix[2][3] * _matrix[3][1] + _matrix[1][3] * _matrix[2][1] * _matrix[3][2]
		- _matrix[1][1] * _matrix[2][3] * _matrix[3][2] - _matrix[1][2] * _matrix[2][1] * _matrix[3][3] - _matrix[1][3] * _matrix[2][2] * _matrix[3][1]);
	inverse._12 = det*(_matrix[0][1] * _matrix[2][3] * _matrix[3][2] + _matrix[0][2] * _matrix[2][1] * _matrix[3][3] + _matrix[0][3] * _matrix[2][2] * _matrix[3][1]
		- _matrix[0][1] * _matrix[2][2] * _matrix[3][3] - _matrix[0][2] * _matrix[2][3] * _matrix[3][1] - _matrix[0][3] * _matrix[2][1] * _matrix[3][1]);
	inverse._13 = det*(_matrix[0][1] * _matrix[1][2] * _matrix[3][3] + _matrix[0][2] * _matrix[1][3] * _matrix[3][1] + _matrix[0][3] * _matrix[1][1] * _matrix[3][2]
		- _matrix[0][1] * _matrix[1][3] * _matrix[3][2] - _matrix[0][2] * _matrix[1][1] * _matrix[3][3] - _matrix[0][3] * _matrix[1][2] * _matrix[3][1]);
	inverse._14 = det*(_matrix[0][1] * _matrix[1][3] * _matrix[2][2] + _matrix[0][2] * _matrix[1][1] * _matrix[2][3] + _matrix[0][3] * _matrix[1][2] * _matrix[2][1]
		- _matrix[0][1] * _matrix[1][2] * _matrix[2][3] - _matrix[0][2] * _matrix[1][3] * _matrix[2][1] - _matrix[0][3] * _matrix[1][1] * _matrix[2][2]);

	inverse._21 = det*(_matrix[1][0] * _matrix[2][3] * _matrix[3][2] + _matrix[1][2] * _matrix[2][0] * _matrix[3][3] + _matrix[1][3] * _matrix[2][2] * _matrix[3][0]
		- _matrix[1][0] * _matrix[2][2] * _matrix[3][3] - _matrix[1][2] * _matrix[2][3] * _matrix[3][0] - _matrix[1][3] * _matrix[2][0] * _matrix[3][2]);
	inverse._22 = det*(_matrix[0][0] * _matrix[2][2] * _matrix[3][3] + _matrix[0][2] * _matrix[2][3] * _matrix[3][0] + _matrix[0][3] * _matrix[2][0] * _matrix[3][2]
		- _matrix[0][0] * _matrix[2][3] * _matrix[3][2] - _matrix[0][2] * _matrix[2][0] * _matrix[3][3] - _matrix[0][3] * _matrix[2][2] * _matrix[3][0]);
	inverse._23 = det*(_matrix[0][0] * _matrix[1][3] * _matrix[3][2] + _matrix[0][2] * _matrix[1][0] * _matrix[3][3] + _matrix[0][3] * _matrix[1][2] * _matrix[3][0]
		- _matrix[0][0] * _matrix[1][2] * _matrix[3][3] - _matrix[0][2] * _matrix[1][0] * _matrix[2][3] - _matrix[0][3] * _matrix[1][2] * _matrix[2][0]);
	inverse._24 = det*(_matrix[0][0] * _matrix[1][2] * _matrix[2][3] + _matrix[0][2] * _matrix[1][3] * _matrix[2][0] + _matrix[0][3] * _matrix[1][0] * _matrix[2][2]
		- _matrix[0][0] * _matrix[1][3] * _matrix[2][2] - _matrix[0][2] * _matrix[1][0] * _matrix[2][3] - _matrix[0][3] * _matrix[1][2] * _matrix[2][0]);

	inverse._31 = det*(_matrix[1][0] * _matrix[2][1] * _matrix[3][3] + _matrix[1][1] * _matrix[2][3] * _matrix[3][0] + _matrix[1][3] * _matrix[2][1] * _matrix[3][0]
		- _matrix[1][0] * _matrix[2][1] * _matrix[3][3] - _matrix[1][1] * _matrix[2][0] * _matrix[3][3] - _matrix[1][3] * _matrix[2][1] * _matrix[3][0]);
	inverse._32 = det*(_matrix[0][0] * _matrix[2][3] * _matrix[3][1] + _matrix[0][1] * _matrix[2][0] * _matrix[3][3] + _matrix[0][3] * _matrix[2][1] * _matrix[3][0]
		- _matrix[0][0] * _matrix[2][1] * _matrix[3][3] - _matrix[0][1] * _matrix[2][3] * _matrix[3][0] - _matrix[0][3] * _matrix[2][0] * _matrix[3][1]);
	inverse._33 = det*(_matrix[0][0] * _matrix[1][1] * _matrix[3][3] + _matrix[0][1] * _matrix[1][3] * _matrix[3][0] + _matrix[0][3] * _matrix[1][0] * _matrix[3][1]
		- _matrix[0][0] * _matrix[1][3] * _matrix[3][1] - _matrix[0][1] * _matrix[1][0] * _matrix[3][3] - _matrix[0][3] * _matrix[1][1] * _matrix[3][0]);
	inverse._34 = det*(_matrix[0][0] * _matrix[1][3] * _matrix[2][1] + _matrix[0][1] * _matrix[1][0] * _matrix[2][3] + _matrix[0][3] * _matrix[1][1] * _matrix[2][0]
		- _matrix[0][0] * _matrix[1][1] * _matrix[2][3] - _matrix[0][1] * _matrix[1][3] * _matrix[2][0] - _matrix[0][3] * _matrix[1][0] * _matrix[2][1]);

	inverse._41 = det*(_matrix[1][0] * _matrix[2][2] * _matrix[3][1] + _matrix[1][1] * _matrix[2][0] * _matrix[3][2] + _matrix[1][2] * _matrix[2][1] * _matrix[3][0]
		- _matrix[1][0] * _matrix[2][1] * _matrix[3][2] - _matrix[1][1] * _matrix[2][2] * _matrix[3][0] - _matrix[1][2] * _matrix[2][0] * _matrix[3][1]);
	inverse._42 = det*(_matrix[0][0] * _matrix[2][1] * _matrix[3][2] + _matrix[0][1] * _matrix[2][2] * _matrix[3][0] + _matrix[0][2] * _matrix[2][0] * _matrix[3][1]
		- _matrix[0][0] * _matrix[2][2] * _matrix[3][1] - _matrix[0][1] * _matrix[2][0] * _matrix[3][2] - _matrix[0][2] * _matrix[2][1] * _matrix[3][0]);
	inverse._43 = det*(_matrix[0][0] * _matrix[1][2] * _matrix[3][1] + _matrix[0][1] * _matrix[1][0] * _matrix[3][2] + _matrix[0][2] * _matrix[1][1] * _matrix[3][0]
		- _matrix[0][0] * _matrix[1][1] * _matrix[3][2] - _matrix[0][1] * _matrix[1][2] * _matrix[3][0] - _matrix[0][2] * _matrix[1][0] * _matrix[3][1]);
	inverse._44 = det*(_matrix[0][0] * _matrix[1][1] * _matrix[2][2] + _matrix[0][1] * _matrix[1][2] * _matrix[2][0] + _matrix[0][2] * _matrix[1][0] * _matrix[2][1]
		- _matrix[0][0] * _matrix[1][2] * _matrix[2][1] - _matrix[0][1] * _matrix[1][0] * _matrix[2][2] - _matrix[0][2] * _matrix[1][1] * _matrix[2][0]);

	*this=inverse;
}

Matrix4x4 Matrix4x4::Multiply(Matrix4x4 in){
	Matrix4x4 out;

	out._11 = _matrix[0][0] * in._matrix[0][0] + _matrix[0][1] * in._matrix[1][0] + _matrix[0][2] * in._matrix[2][0] + _matrix[0][3] * in._matrix[3][0];
	out._12 = _matrix[0][0] * in._matrix[0][1] + _matrix[0][1] * in._matrix[1][1] + _matrix[0][2] * in._matrix[2][1] + _matrix[0][3] * in._matrix[3][1];
	out._13 = _matrix[0][0] * in._matrix[0][2] + _matrix[0][1] * in._matrix[1][2] + _matrix[0][2] * in._matrix[2][2] + _matrix[0][3] * in._matrix[3][2];
	out._14 = _matrix[0][0] * in._matrix[0][3] + _matrix[0][1] * in._matrix[1][3] + _matrix[0][2] * in._matrix[2][3] + _matrix[0][3] * in._matrix[3][3];

	out._21 = _matrix[1][0] * in._matrix[0][0] + _matrix[1][1] * in._matrix[1][0] + _matrix[1][2] * in._matrix[2][0] + _matrix[1][3] * in._matrix[3][0];
	out._22 = _matrix[1][0] * in._matrix[0][1] + _matrix[1][1] * in._matrix[1][1] + _matrix[1][2] * in._matrix[2][1] + _matrix[1][3] * in._matrix[3][1];
	out._23 = _matrix[1][0] * in._matrix[0][2] + _matrix[1][1] * in._matrix[1][2] + _matrix[1][2] * in._matrix[2][2] + _matrix[1][3] * in._matrix[3][2];
	out._24 = _matrix[1][0] * in._matrix[0][3] + _matrix[1][1] * in._matrix[1][3] + _matrix[1][2] * in._matrix[2][3] + _matrix[1][3] * in._matrix[3][3];

	out._31 = _matrix[2][0] * in._matrix[0][0] + _matrix[2][1] * in._matrix[1][0] + _matrix[2][2] * in._matrix[2][0] + _matrix[2][3] * in._matrix[3][0];
	out._32 = _matrix[2][0] * in._matrix[0][1] + _matrix[2][1] * in._matrix[1][1] + _matrix[2][2] * in._matrix[2][1] + _matrix[2][3] * in._matrix[3][1];
	out._33 = _matrix[2][0] * in._matrix[0][2] + _matrix[2][1] * in._matrix[1][2] + _matrix[2][2] * in._matrix[2][2] + _matrix[2][3] * in._matrix[3][2];
	out._34 = _matrix[2][0] * in._matrix[0][3] + _matrix[2][1] * in._matrix[1][3] + _matrix[2][2] * in._matrix[2][3] + _matrix[2][3] * in._matrix[3][3];

	out._41 = _matrix[3][0] * in._matrix[0][0] + _matrix[3][1] * in._matrix[1][0] + _matrix[3][2] * in._matrix[2][0] + _matrix[3][3] * in._matrix[3][0];
	out._42 = _matrix[3][0] * in._matrix[0][1] + _matrix[3][1] * in._matrix[1][1] + _matrix[3][2] * in._matrix[2][1] + _matrix[3][3] * in._matrix[3][1];
	out._43 = _matrix[3][0] * in._matrix[0][2] + _matrix[3][1] * in._matrix[1][2] + _matrix[3][2] * in._matrix[2][2] + _matrix[3][3] * in._matrix[3][2];
	out._44 = _matrix[3][0] * in._matrix[0][3] + _matrix[3][1] * in._matrix[1][3] + _matrix[3][2] * in._matrix[2][3] + _matrix[3][3] * in._matrix[3][3];
	
	return out;
}


void Matrix4x4::PerspectiveFovLH(float fov, float aspect, float zNear, float zFar){
	float h = 1.0 / tanf(fov / 2.0f);
	float w = h / aspect;

	this->Identity();
	_11 = w;
	_22 = h;

	_33 = zFar / (zFar - zNear);
	_34 = 1.0f;

	_43 = -zNear*zFar / (zFar - zNear);
	_44 = 0.0f;
}


void Matrix4x4::PerspectiveFovRH(float fov, float aspect, float zNear, float zFar){
	float h = 1.0 / tanf(fov / 2.0f);
	float w = h / aspect;

	this->Identity();
	_11 = w;
	_22 = h;

	_33 = zFar / (zFar - zNear);
	_34 = -1.0f;

	_43 = -zNear*zFar / (zFar - zNear);
	_44 = 0.0f;
}

void Matrix4x4::PerspectiveLH(float width, float height, float zNear, float zFar){
	this->Identity();
	_11 = 2 * zNear / width;
	_22 = 2 * zNear / height;

	_33 = zFar / (zFar - zNear);
	_34 = 1.0f;

	_43 = zNear*zFar / (zFar - zNear);
	_44 = 0.0f;

}

void Matrix4x4::PerspectiveRH(float width, float height, float zNear, float zFar){
	this->Identity();
	_11 = 2 * zNear / width;
	_22 = 2 * zNear / height;

	_33 = zFar / (zFar - zNear);
	_34 = -1.0f;

	_43 = zNear*zFar / (zFar - zNear);
	_44 = 0.0f;

}

void Matrix4x4::OrthoLH(float width, float height, float zNear, float zFar){
	this->Identity();
	_11 = 2 / width;
	_22 = 2 / height;
	
	_33 = 1 / (zFar - zNear);
	_34 = 1.0f;

	_43 = zNear / (zNear - zFar);
	_44 = 0.0f;

}
void Matrix4x4::OrthoRH(float width, float height, float zNear, float zFar){
	this->Identity();
	_11 = 2 / width;
	_22 = 2 / height;

	_33 = 1 / (zFar - zNear);
	_34 = -1.0f;

	_43 = zNear / (zNear - zFar);
	_44 = 0.0f;

}

void Matrix4x4::LookAtLH(Vector3 pos, Vector3 target, Vector3 up){
	Vector3 zaxis = (target - pos).Normalize();
	Vector3 xaxis = (up.Cross(zaxis)).Normalize();
	Vector3 yaxis = zaxis.Cross(xaxis);

	_11 = xaxis._x; _12 = yaxis._x; _13 = zaxis._x; _14 = 0.0f;
	_21 = xaxis._y; _22 = yaxis._y; _23 = zaxis._y; _24 = 0.0f;
	_31 = xaxis._z; _32 = yaxis._z; _33 = zaxis._z; _34 = 0.0f;

	_41 = -Vector3(xaxis).Dot(pos);
	_42 = -Vector3(yaxis).Dot(pos);
	_43 = -Vector3(zaxis).Dot(pos);
	_44 = 1.0f;
}

/*************************
	operators
*/
Matrix4x4 Matrix4x4::operator +(){
	return *this;
}
Matrix4x4 Matrix4x4::operator-(){
	return Matrix4x4(
		-_11, -_12, -_13, -_14,
		-_21, -_22, -_23, -_24,
		-_31, -_32, -_33, -_34,
		-_41, -_42, -_43, -_44
		);
}

Matrix4x4 Matrix4x4::operator+(Matrix4x4 in){
	return 	Matrix4x4(
		_11 + in._11, _12 + in._12, _13 + in._13, _14 + in._14,
		_21 + in._21, _22 + in._22, _23 + in._23, _24 + in._24,
		_31 + in._31, _32 + in._32, _33 + in._33, _34 + in._34,
		_41 + in._41, _42 + in._42, _43 + in._43, _44 + in._44
		);
}

Matrix4x4 Matrix4x4::operator-(Matrix4x4 in){
	return Matrix4x4(*this + (-in));
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 in){
	Matrix4x4 out;
	out = this->Multiply(in);
	return out;
}

void Matrix4x4::operator+=(Matrix4x4 in){
	*this = *this + in;
}
void Matrix4x4::operator-=(Matrix4x4 in){
	*this = *this - in;
}
void Matrix4x4::operator*=(Matrix4x4 in){
	*this = this->Multiply(in);
}

Matrix4x4 Matrix4x4::operator+(float in){
	return 	Matrix4x4(
		_11 + in, _12 + in, _13 + in, _14 + in,
		_21 + in, _22 + in, _23 + in, _24 + in,
		_31 + in, _32 + in, _33 + in, _34 + in,
		_41 + in, _42 + in, _43 + in, _44 + in
		);
}
Matrix4x4 Matrix4x4::operator-(float in){
	return Matrix4x4(*this + (-in));
}
Matrix4x4 Matrix4x4::operator*(float in){
	return 	Matrix4x4(
		_11 * in, _12 * in, _13 * in, _14 * in,
		_21 * in, _22 * in, _23 * in, _24 * in,
		_31 * in, _32 * in, _33 * in, _34 * in,
		_41 * in, _42 * in, _43 * in, _44 * in
		);
}
Matrix4x4 Matrix4x4::operator/(float in){
	float fInv = 1.0 / in;
	return Matrix4x4(*this * in);
}
void Matrix4x4::operator+=(float in){
	*this = *this + in;
}
void Matrix4x4::operator-=(float in){
	*this = *this - in;
}
void Matrix4x4::operator*=(float in){
	*this = *this * in;
}

Vector3 Matrix4x4::operator*(Vector3 in){
	Vector3 out;
	out._x = in._x*_11 + in._y*_21 + in._z*_31 + _41;
	out._y = in._x*_12 + in._y*_22 + in._z*_32 + _42;
	out._z = in._x*_13 + in._y*_23 + in._z*_33 + _43;
	return out;
}
Vector4 Matrix4x4::operator*(Vector4 in){
	Vector4 out;
	out._x = in._x*_11 + in._y*_21 + in._z*_31 + in._w*_41;
	out._y = in._x*_12 + in._y*_22 + in._z*_32 + in._w*_42;
	out._z = in._x*_13 + in._y*_23 + in._z*_33 + in._w*_43;
	out._w = in._x*_14 + in._y*_24 + in._z*_34 + in._w*_44;

	return out;

}





