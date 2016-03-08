#include "Vector2.h"
#include <math.h>
using namespace aetherClass;
using namespace DirectX;
	Vector2::Vector2(){
		_x = 0.0f;
		_y = 0.0f;
	}

	Vector2::Vector2(float x, float y){
		_x = x;
		_y = y;
	}
	
	

	Vector2::~Vector2()
	{
		_x = 0.0f;
		_y = 0.0f;
	}


	float Vector2::GetVectorLength(){
		float length;

		length = sqrtf((_x*_x) + (_y*_y));

		return length;
	}


	Vector2 Vector2::Normalize(){
		Vector2 output;
		float length = GetVectorLength();
		output._x = _x / length;
		output._y = _y / length;
		return output;
	}

	float Vector2::Dot(Vector2& input)
	{
		float output;
		output = (this->_x*input._x) + (this->_y*input._y);
		return output;
	}


	/*	‘ã“ü		*/
	void Vector2::operator = (float input){
		_x = input;
		_y = input;
		return;
	}

	/*	˜aZ		*/
	Vector2 Vector2::operator + (Vector2 input){
		Vector2 output;
		output._x = _x + input._x;
		output._y = _y + input._y;

		return output;
	}

	void Vector2::operator += (Vector2 input){

		_x += input._x;
		_y += input._y;

		return;
	}

	Vector2 Vector2::operator + (float input){
		Vector2 output;
		output._x = _x + input;
		output._y = _y + input;

		return output;
	}

	void Vector2::operator += (float input){

		_x += input;
		_y += input;
		return;
	}

	/*	Œ¸Z		*/
	Vector2 Vector2::operator - (Vector2 input){
		Vector2 output;
		output._x = _x - input._x;
		output._y = _y - input._y;

		return output;
	}

	void Vector2::operator -= (Vector2 input){

		_x -= input._x;
		_y -= input._y;
		return;
	}

	Vector2 Vector2::operator - (float input){
		Vector2 output;
		output._x = _x - input;
		output._y = _y - input;

		return output;
	}

	void Vector2::operator -= (float input){

		_x -= input;
		_y -= input;
		return;
	}

	/*	ÏZ		*/
	Vector2 Vector2::operator * (float input){
		Vector2 output;
		output._x = _x * input;
		output._y = _y * input;

		return output;
	}


	void Vector2::operator *= (float input){

		_x *= input;
		_y *= input;

		return;
	};
	//¤Z
	Vector2 Vector2::operator / (float input){
		Vector2 output;
		output._x = _x / input;
		output._y = _y / input;

		return output;
	}


	void  Vector2::operator /= (float input){

		_x /= input;
		_y /= input;
		return;
	}

	//”äŠr
	bool  Vector2::operator == (Vector2 input){
		if (_x != input._x ||
			_y != input._y)
		{
			return false;
		}
		return true;
	}

	bool  Vector2::operator != (Vector2 input){
		if (_x == input._x ||
			_y == input._y)
		{
			return false;
		}
		return true;
	}

	bool Vector2::operator < (Vector2 input){

		if (_x < input._x ||
			_y < input._y)
		{
			return false;
		}
		return true;
	}

	bool Vector2::operator <= (Vector2 input){

		if (_x <= input._x ||
			_y <= input._y)
		{
			return false;
		}
		return true;
	}

	bool Vector2::operator > (Vector2 input){

		if (_x > input._x ||
			_y > input._y)
		{
			return false;
		}
		return true;
	}

	bool Vector2::operator >= (Vector2 input){

		if (_x >= input._x ||
			_y >= input._y)
		{
			return false;
		}
		return true;
	}

