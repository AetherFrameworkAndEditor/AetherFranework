#include "Quaternion.h"
#include <math.h>
using namespace aetherClass;

const Quaternion Quaternion::_identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

//
Quaternion::Quaternion()
{
}

//
Quaternion::~Quaternion()
{
}

//
Quaternion::Quaternion(const float x, const float y, const float z, const float w){
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}

//
Quaternion::Quaternion(const Vector3 axis, const float radian){
	float axisX = axis._x;
	float axisY = axis._y;
	float axisZ = axis._z;

	float length = (axisX*axisX) + (axisY*axisY) + (axisZ*axisZ);

	// ê≥ãKâªÇ≥ÇÍÇƒÇ¢Ç»ÇØÇÍÇŒê≥ãKâª
	if (length != 1.0f)
	{
		length = sqrtf(length);

		axisX /= length;
		axisY /= length;
		axisZ /= length;
	}

	float Sin, Cosin;
	Sin = sin(radian);
	Cosin = cos(radian);

	_x = Sin*axisX;
	_y = Sin*axisY;
	_z = Sin*axisZ;
	_w = Cosin;
}

//
void Quaternion::SetElement(const float x, const float y, const float z, const float w){
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}

//
float Quaternion::GetLength()const{
	float length;

	length = sqrtf((_x*_x) + (_y*_y) + (_z * _z) + (_w*_w));

	return length;
}

//
float Quaternion::GetLengthSquared()const{
	float length;

	length = (_x*_x) + (_y*_y) + (_z * _z) + (_w*_w);

	return length;
}

//
Quaternion Quaternion::Normalize(){
	float normalize = GetLength();

	Quaternion out;
	out._x /= normalize;
	out._y /= normalize;
	out._z /= normalize;
	out._w /= normalize;

	return out;
}

//
bool Quaternion::isIdentity(){

	return true;
}

//
Quaternion Quaternion::Multiply(const Quaternion& qua){
	float lx = _x;
	float ly = _y;
	float lz = _z;
	float lw = _w;
	Quaternion out;
	out._x = (qua._x*lw + lx*qua._w + qua._y*lz) - (qua._z*ly);
	out._y = (qua._y*lw + ly*qua._w + qua._z*lz) - (qua._x*lz);
	out._z = (qua._z*lw + lz*qua._w + qua._x*lz) - (qua._y*lx);
	out._w = (qua._w*lw) - (qua._x*lx + qua._y*ly + qua._z*lz);

	return out;
}

//
void Quaternion::RotationByX(const float angle){

	const float Sin = sin(angle*0.5);
	const float Cosin = cos(angle*0.5);

	const float lx = _x;
	const float ly = _y;
	const float lz = _z;
	const float lw = _w;

	_x = (Sin*lw + lx*Cosin);
	_y = (ly*Cosin) - (Sin*lz);
	_z = (lz*Cosin) + (Sin*ly);
	_w = (Cosin*lw) - (Sin*lx);

	return;
}

//
void Quaternion::RotationByY(const float angle){
	const float Sin = sin(angle*0.5);
	const float Cosin = cos(angle*0.5);

	const float lx = _x;
	const float ly = _y;
	const float lz = _z;
	const float lw = _w;

	_x = (lx*Cosin) + (Sin*lz);
	_y = (Sin*lw) + (ly*Cosin);
	_z = (lz*Cosin) - (Sin*lx);
	_w = (Cosin*lw) - (Sin*ly);

	return;
}

//
void Quaternion::RotationByZ(const float angle){
	const float Sin = sin(angle*0.5);
	const float Cosin = cos(angle*0.5);

	const float lx = _x;
	const float ly = _y;
	const float lz = _z;
	const float lw = _w;

	_x = (lx*Cosin) - (Sin*ly);
	_y = (Cosin*ly) + (lx*Sin);
	_z = (Sin*lw) + (lz*Cosin);
	_w = (Cosin*lw) - (Sin*lz);

	return;
}


//
Matrix4x4 Quaternion::Matrix4x4FromQuaternion(){
	Matrix4x4 outMatrix;
	outMatrix = Matrix4x4
		(1 - (2 * (_y*_y) + 2 * (_z*_z)), (2 * ((_x*_y) - 2 * (_w*_z))), (2 * ((_w*_y) + 2 * (_x*_z))), 0,
		(2 * (_x*_y) + 2 * (_w*_z)), 1 - (2 * (_x*_x) + 2 * (_z*_z)), (2 * (_y*_z) - 2 * (_w*_x)), 0,
		(2 * (_x*_z) - 2 * (_w*_y)), (2 * (_y*_z) + 2 * (_w*_x)), 1 - (2 * (_x*_x) + 2 * (_y*_y)), 0,
		0, 0, 0, 1);
	return outMatrix;
}