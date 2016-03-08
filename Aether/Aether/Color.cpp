#include "Color.h"

using namespace aetherClass;
Color::Color(){
	_red = 0.0f;
	_green = 0.0f;
	_blue = 0.0f;
	_alpha = 1.0f;
}

Color::~Color(){
	_red = 0.0f;
	_green = 0.0f;
	_blue = 0.0f;
	_alpha = 0.0f;
}

Color::Color(float r, float g, float b, float a){
	_red = r;
	_green = g;
	_blue = b;
	_alpha = a;
}

Color::Color(Vector4 in){
	*this = in;
}
Color::Color(Vector3 in){
	*this = in;
}
Color::Color(float in){
	*this = in;
}

/*	‘ã“ü		*/
void Color::operator =(Vector3 input){
	_red = input._x;
	_green = input._y;
	_blue = input._z;
	_alpha = 1.0f;
}
void Color::operator =(Vector4 input){
	_red = input._x;
	_green = input._y;
	_blue = input._z;
	_alpha = input._w;
}
void Color::operator =(float input){
	_red = input;
	_green = input;
	_blue = input;
	_alpha = input;
}

