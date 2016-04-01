#include "ViewCamera.h"
#include "MathUtility.h"
using namespace aetherClass;
using namespace DirectX;

ViewCamera::ViewCamera(){
	SecureZeroMemory(&property, sizeof(property));
	
	property._lookUp._y = 1.0f;
	property._lookAt._z = 1.0f;
}


void ViewCamera::Render(){
	Vector3 up, position, lookat;
	float yaw, pitch, roll;
	Matrix4x4 rotationMatrix;

	// Setup the vector that points upwards
	up._x = property._lookUp._x;
	up._y = property._lookUp._y;
	up._z = property._lookUp._z;

	// Setup the vector that points of the camera in the world
	position._x = property._translation._x;
	position._y = property._translation._y;
	position._z = property._translation._z;

	// Setup where the camera is looking by default
	lookat._x = property._lookAt._x;
	lookat._y = property._lookAt._y;
	lookat._z = property._lookAt._z;

	// Set the yaw(Y axis),pitch(X axis),and roll(Z axis)m_rotation in randians
	pitch = property._rotation._x*kAetherRadian;
	yaw = property._rotation._y*kAetherRadian;
	roll = property._rotation._z* kAetherRadian;

	// Create the m_rotation matrix from the yaw,pitch,and roll values
	rotationMatrix.PitchYawRoll(Vector3(pitch, yaw, roll));

	// Transform the m_lookAt and up vector by the m_rotation matrix so the view is correctty rotated at the origin
	lookat = lookat.TransformCoord(rotationMatrix);
	up = up.TransformCoord(rotationMatrix);

	// Translate the rotated camera position to the location of the viewer
	lookat = position + lookat;

	// Finally create the view matrix from the three updata vectors
	m_viewMatrix.LookAtLH(position, lookat, up);

	return;
}



////////////////////
//Accessor Methods
//
Matrix4x4 ViewCamera::GetViewMatrix(){
	
	return m_viewMatrix;
}

#include<iostream>
//Debug Controller
#ifdef DEBUG_MODE
#include"GameController.h"
void ViewCamera::Controller(){

	static float cm_trans = 0.2f;
	static float cm_rote = 1.0f;

	float trans_accelVal = 0.2f;
	float rote_accelVal = 0.5f;

	static int count = 0;
	Vector3 translation;
	Vector3 rotation;

	bool IsKeyDown = false;
	if (GameController::GetKey().IsKeyDown(VK_LCONTROL)){

		if (GameController::GetKey().IsKeyDown('W')){
			rotation._x += cm_rote;
		}
		else if (GameController::GetKey().IsKeyDown('S')){
			rotation._x -= cm_rote;
		}
		if (GameController::GetKey().IsKeyDown('Q')){
			rotation._z += cm_rote;
		}
		else if (GameController::GetKey().IsKeyDown('W')){
			rotation._z -= cm_rote;
		}
		if (GameController::GetKey().IsKeyDown('D')){
			rotation._y += cm_rote;
		}
		else if (GameController::GetKey().IsKeyDown('A')){
			rotation._y -= cm_rote;
		}
		IsKeyDown = true;
	}
	else{
		if (GameController::GetKey().IsKeyDown('E')){
			rotation._y += cm_rote;
		}
		else if (GameController::GetKey().IsKeyDown('Q')){
			rotation._y -= cm_rote;
		}
		if (GameController::GetKey().IsKeyDown('A')){
			translation._x -= cm_trans;
		}
		else if (GameController::GetKey().IsKeyDown('D')){
			translation._x += cm_trans;
		}
		if (GameController::GetKey().IsKeyDown('W')){
			translation._z += cm_trans;
		}
		else if (GameController::GetKey().IsKeyDown('S')){
			translation._z -= cm_trans;
		}
		if (GameController::GetKey().IsKeyDown(VK_SPACE)){
			translation._y += cm_trans;
		}
		else if (GameController::GetKey().IsKeyDown(VK_LSHIFT)){
			translation._y -= cm_trans;
		}

	}
	if (!(translation == Vector3(0, 0, 0))){
		count++;
		IsKeyDown = true;
		if (count % 50 == 0){
			cm_trans += trans_accelVal;
		}
	}
	if (!(rotation == Vector3(0, 0, 0))){
		count++;
		IsKeyDown = true;
		if (count % 30 == 0){
			cm_rote += rote_accelVal;
		}
	}

	if (IsKeyDown){
		property._rotation += rotation;
		Matrix4x4 roteMat;
		Vector3 roteVec = property._rotation;
		roteVec *= kAetherRadian;

		roteMat.PitchYawRoll(roteVec);
		translation = translation.TransformCoordNormal(roteMat);

		property._translation._x += translation._x;
		property._translation._y += translation._y;
		property._translation._z += translation._z;
	}
	if (!IsKeyDown){
		count = 0;
		cm_trans = trans_accelVal;
		cm_rote = rote_accelVal;

	}


}
#endif
