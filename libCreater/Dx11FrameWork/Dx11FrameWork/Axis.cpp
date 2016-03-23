#include "Axis.h"
#include"MathUtility.h"

#include<stddef.h> //NULL
#include<DirectXMath.h>
#include"Matrix4x4.h"

using namespace aetherClass;
Axis::Axis(){
	_axisX = NULL;
	_axisY = NULL;
	_axisZ = NULL;
}
Axis::Axis(Vector3 axisX, Vector3 axisY, Vector3 axisZ){
	_axisX = axisX;
	_axisY = axisY;
	_axisZ = axisZ;
}
Axis::~Axis(){
	_axisX = NULL;
	_axisY = NULL;
	_axisZ = NULL;
}

void Axis::Update(Vector3 rotation)
{
	float pitch, yaw, roll;
	pitch = rotation._x * kAetherRadian;
	yaw = rotation._y * kAetherRadian;
	roll = rotation._z * kAetherRadian;

	Matrix4x4 rot;
	rot.PitchYawRoll(Vector3(pitch, yaw, roll));

	_axisX = rot*Vector3(1, 0, 0);
	_axisY = rot*Vector3(0, 1, 0);
	_axisZ = rot*Vector3(0, 0, 1);

}