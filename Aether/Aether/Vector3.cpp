/******************************************************************************/
/*! @addtogroup aetherClass
@file      Vector3.h
@brief     3ŸŒ³ƒxƒNƒgƒ‹ƒNƒ‰ƒX

*******************************************************************************
@date       2015/12/23
@author     ‹´–{q
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/23 ‹´–{q
-# Initial Version
- 2016/1/6 23:00	‹àq˜a÷
-# Add TransformCoord.
- 2016/1/6 23:00	‹´–{q
-# GetVectorLength()‚Ì®‚ğC³
   -#before: length = sqrtf((_x*_x) + (_y*_y) + (_z + _z));
   -#after : length = sqrtf((_x*_x) + (_y*_y) + (_z * _z));

******************************************************************************/

#include "Vector3.h"
#include <math.h>
#include"Matrix4x4.h"
using namespace aetherClass;
using namespace DirectX;
	Vector3::Vector3(){
		_x = _y = _z = 0;
	}

	Vector3::Vector3(float x, float y, float z){
		_x = x;
		_y = y;
		_z = z;
	}

	Vector3::~Vector3()
	{
		_x = _y = _z = 0;
	}

	float Vector3::GetVectorLength(){
		float length;

		length = sqrtf((_x*_x) + (_y*_y) + (_z * _z));

		return length;
	}


	Vector3 Vector3::Normalize(){

		Vector3 output;
		float length = GetVectorLength();
		output._x = _x / length;
		output._y = _y / length;
		output._z = _z / length;

		return output;
	}

	float Vector3::Dot(Vector3& vec)
	{
		float dot = this->_x*vec._x + this->_y*vec._y + this->_z*vec._z;
		return dot;
	}

	Vector3 Vector3::Cross(Vector3& vec)
	{

		Vector3 cross;

		cross._x = this->_y*vec._z - this->_z*vec._y;
		cross._y = this->_z*vec._x - this->_x*vec._z;
		cross._z = this->_x*vec._y - this->_y*vec._x;

		return cross;
	}

	Vector3 Vector3::TransformCoord(Matrix4x4 m){
	
		float w = 1.0f / (this->_x * m._matrix[0][3] + this->_y * m._matrix[1][3] + this->_z * m._matrix[2][3] + m._matrix[3][3]);

		Vector3 output;
		output._x = (this->_x * m._matrix[0][0] + this->_y * m._matrix[1][0] + this->_z * m._matrix[2][0] + m._matrix[3][0]) * w;
		output._y = (this->_x * m._matrix[0][1] + this->_y * m._matrix[1][1] + this->_z * m._matrix[2][1] + m._matrix[3][1]) * w;
		output._z = (this->_x * m._matrix[0][2] + this->_y * m._matrix[1][2] + this->_z * m._matrix[2][2] + m._matrix[3][2]) * w;
		return output;
	}

	/*	‘ã“ü		*/

	void Vector3::operator =(float input){
		_x = input;
		_y = input;
		_z = input;
	}

	/*	˜aZ		*/
	Vector3 Vector3::operator + (Vector3 input){
		Vector3 output;
		output._x = _x + input._x;
		output._y = _y + input._y;
		output._z = _z + input._z;

		return output;
	}

	void Vector3::operator += (Vector3 input){

		_x += input._x;
		_y += input._y;
		_z += input._z;
		return;
	}

	Vector3 Vector3::operator + (float input){
		Vector3 output;
		output._x = _x + input;
		output._y = _y + input;
		output._z = _z + input;

		return output;
	}

	void Vector3::operator += (float input){

		_x += input;
		_y += input;
		_z += input;
		return;
	}

	/*	Œ¸Z		*/
	Vector3 Vector3::operator - (Vector3 input){
		Vector3 output;
		output._x = _x - input._x;
		output._y = _y - input._y;
		output._z = _z - input._z;

		return output;
	}

	void Vector3::operator -= (Vector3 input){

		_x -= input._x;
		_y -= input._y;
		_z -= input._z;
		return;
	}

	Vector3 Vector3::operator - (float input){
		Vector3 output;
		output._x = _x - input;
		output._y = _y - input;
		output._z = _z - input;

		return output;
	}

	void Vector3::operator -= (float input){

		_x -= input;
		_y -= input;
		_z -= input;
		return;
	}




	/*	ÏZ		*/
	Vector3 Vector3::operator * (float input){
		Vector3 output;
		output._x = _x * input;
		output._y = _y * input;
		output._z = _z * input;

		return output;
	}

	void Vector3::operator *= (float input){

		_x *= input;
		_y *= input;
		_z *= input;
		return;
	};
	//¤Z
	Vector3 Vector3::operator / (float input){
		Vector3 output;
		output._x = _x / input;
		output._y = _y / input;
		output._z = _z / input;

		return output;
	}


	void  Vector3::operator /= (float input){

		_x /= input;
		_y /= input;
		_z /= input;
		return;
	}

	//”äŠr
	bool  Vector3::operator == (Vector3 input){
		if (_x != input._x ||
			_y != input._y ||
			_z != input._z)
		{
			return false;
		}
		return true;
	}

	bool  Vector3::operator != (Vector3 input){
		if (_x == input._x ||
			_y == input._y ||
			_z == input._z)
		{
			return false;
		}
		return true;
	}

	bool Vector3::operator < (Vector3 input){

		if (_x < input._x ||
			_y < input._y ||
			_z < input._z)
		{
			return false;
		}
		return true;
	}

	bool Vector3::operator <= (Vector3 input){

		if (_x <= input._x ||
			_y <= input._y ||
			_z <= input._z)
		{
			return false;
		}
		return true;
	}

	bool Vector3::operator > (Vector3 input){

		if (_x > input._x ||
			_y > input._y ||
			_z > input._z)
		{
			return false;
		}
		return true;
	}

	bool Vector3::operator >= (Vector3 input){

		if (_x >= input._x ||
			_y >= input._y ||
			_z >= input._z)
		{
			return false;
		}
		return true;
	}