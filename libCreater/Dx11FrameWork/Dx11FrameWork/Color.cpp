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

/*	‘ã“ü	*/
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


Color Color::operator-(){
	return Color(-_red, -_green, -_blue, -_alpha);
}

Color Color::operator + (Color input){
	Color out;
	out._red = _red + input._red;
	out._blue = _blue + input._blue;
	out._green = _green + input._green;
	out._alpha = _alpha + input._alpha;
	return out;
}
Color Color::operator + (Vector3 input){
	Color out(input);
	out = *this + out;
	return out;
}
Color Color::operator + (Vector4 input){
	Color out(input);
	out = *this + out;
	return out;

}
Color Color::operator + (float input){
	Color out(input);
	out = *this + out;
	return out;
}

void Color::operator += (Color input){
	*this = *this + input;
}
void Color::operator += (Vector3 input){
	*this = *this + input;

}
void Color::operator += (Vector4 input){
	*this = *this + input;

}
void Color::operator += (float input){
	*this = *this + input;

}

Color Color::operator - (Color input){
	Color out(input);
	out = *this + (-out);
	return out;
}
Color Color::operator - (Vector3 input){
	Color out(input);
	out = *this + (-out);
	return out;

}
Color Color::operator - (Vector4 input){
	Color out(input);
	out = *this + (-out);
	return out;

}
Color Color::operator - (float input){
	Color out(input);
	out = *this + (-out);
	return out;

}

void Color::operator -= (Color input){
	*this = *this - input;
}
void Color::operator -= (Vector3 input){
	*this = *this - input;
}
void Color::operator -= (Vector4 input){
	*this = *this - input;
}
void Color::operator -= (float input){
	*this = *this - input;
}

