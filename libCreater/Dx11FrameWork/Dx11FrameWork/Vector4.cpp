#include "Vector4.h"
#include "Vector3.h"
#include <math.h>
using namespace aetherClass;
using namespace DirectX;
	Vector4::Vector4(){
		_x = 0.0f;
		_y = 0.0f;
		_z = 0.0f;
		_w = 0.0f;
	}


	Vector4::~Vector4(){
		_x = 0.0f;
		_y = 0.0f;
		_z = 0.0f;
		_w = 0.0f;
	}

	Vector4::Vector4(float x, float y, float z, float w){
		_x = x;
		_y = y;
		_z = z;
		_w = w;
	}
	Vector4::Vector4(Vector3 vector3){
		_x = vector3._x;
		_y = vector3._y;
		_z = vector3._z;
		_w = 0.0f;
	}
	Vector4::Vector4(const Vector4& vector4){
		_x = vector4._x;
		_y = vector4._y;
		_z = vector4._z;
		_w = vector4._w;
	}

	float Vector4::GetVectorLength(){
		float length;
		length = sqrtf((_x*_x) + (_y*_y) + (_z * _z) + (_w*_w));

		return length;
	}

	Vector4 Vector4::Normalize(){
		float length = GetVectorLength();
		Vector4 output = *this;
		output._x /= length;
		output._y /= length;
		output._z /= length;
		output._w /= length;
		return output;
	}

	float Vector4::Dot(Vector4& input)
	{
		float output;
		output = ((_x*input._x) + (_y*input._y) + (_z*input._z) + (_w*input._w));
		return output;
	}

	Vector4 Vector4::Cross(Vector4& input)
	{
		Vector4 output;
		output._x = _y*input._z - _z*input._y;
		output._y = _z*input._x - _x*input._z;
		output._z = _x*input._y - _y*input._x;
		output._w = 0.0f;

		return output;
	}


	/*	‘ã“ü		*/
	void Vector4::operator = (Vector4& input){
		_x = input._x;
		_y = input._y;
		_z = input._z;
		_w = input._w;
		return;
	}


	void Vector4::operator =(Vector3& input){
		_x = input._x;
		_y = input._y;
		_z = input._z;
		_w = 0.0f;
	}

	void Vector4::operator =(float input){
		_x = input;
		_y = input;
		_z = input;
		_w = 0.0f;
	}

	/*	˜aZ		*/
	Vector4 Vector4::operator + (Vector4 input){
		Vector4 output;
		output._x = _x + input._x;
		output._y = _y + input._y;
		output._z = _z + input._z;
		output._w = _w + input._w;

		return output;
	}

	void Vector4::operator += (Vector4 input){

		_x += input._x;
		_y += input._y;
		_z += input._z;
		_w += input._w;
		return;
	}

	Vector4 Vector4::operator + (float input){
		Vector4 output;
		output._x = _x + input;
		output._y = _y + input;
		output._z = _z + input;
		output._w = _w + input;
		return output;
	}

	void Vector4::operator += (float input){

		_x += input;
		_y += input;
		_z += input;
		return;
	}

	/*	Œ¸Z		*/
	Vector4 Vector4::operator - (Vector4 input){
		Vector4 output;
		output._x = _x - input._x;
		output._y = _y - input._y;
		output._z = _z - input._z;
		output._w = _w - input._w;
		return output;
	}

	void Vector4::operator -= (Vector4 input){

		_x -= input._x;
		_y -= input._y;
		_z -= input._z;
		_w -= input._w;
		return;
	}

	Vector4 Vector4::operator - (float input){
		Vector4 output;
		output._x = _x - input;
		output._y = _y - input;
		output._z = _z - input;
		output._w = _w - input;
		return output;
	}

	void Vector4::operator -= (float input){

		_x -= input;
		_y -= input;
		_z -= input;
		_w -= input;
		return;
	}

	/*	ÏZ		*/
	Vector4 Vector4::operator * (float input){
		Vector4 output;
		output._x = _x * input;
		output._y = _y * input;
		output._z = _z * input;

		return output;
	}

	void Vector4::operator *= (float input){

		_x *= input;
		_y *= input;
		_z *= input;
		return;
	};


	//¤Z
	Vector4 Vector4::operator / (float input){
		Vector4 output;
		output._x = _x / input;
		output._y = _y / input;
		output._z = _z / input;

		return output;
	}


	void  Vector4::operator /= (float input){

		_x /= input;
		_y /= input;
		_z /= input;
		return;
	}

	//”äŠr
	bool  Vector4::operator == (Vector4 input){
		if (_x != input._x ||
			_y != input._y ||
			_z != input._z ||
			_w != input._w)
		{
			return false;
		}
		return true;
	}

	bool  Vector4::operator != (Vector4 input){
		if (_x == input._x ||
			_y == input._y ||
			_z == input._z ||
			_w == input._w)
		{
			return false;
		}
		return true;
	}

	bool Vector4::operator < (Vector4 input){

		if (_x < input._x ||
			_y < input._y ||
			_z < input._z ||
			_w < input._w)
		{
			return false;
		}
		return true;
	}

	bool Vector4::operator <= (Vector4 input){

		if (_x <= input._x ||
			_y <= input._y ||
			_z <= input._z ||
			_w <= input._w)
		{
			return false;
		}
		return true;
	}

	bool Vector4::operator > (Vector4 input){

		if (_x > input._x ||
			_y > input._y ||
			_z > input._z ||
			_w > input._w)
		{
			return false;
		}
		return true;
	}

	bool Vector4::operator >= (Vector4 input){

		if (_x >= input._x ||
			_y >= input._y ||
			_z >= input._z ||
			_w >= input._w)
		{
			return false;
		}
		return true;
	}

