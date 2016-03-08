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


//Debug Controller
#ifdef DEBUG_MODE
#include"GameController.h"
void ViewCamera::Controller(){

	static float cm_move = 0.2f;


	if (GameController::GetKey().IsKeyDown(DIK_LCONTROL)){

		if (GameController::GetKey().IsKeyDown(DIK_W)){
			property._rotation._x += cm_move * 4;
		}
		else if (GameController::GetKey().IsKeyDown(DIK_S)){
			property._rotation._x -= cm_move * 4;
		}
		if (GameController::GetKey().IsKeyDown(DIK_Q)){
			property._rotation._z += cm_move * 4;
		}
		else if (GameController::GetKey().IsKeyDown(DIK_E)){
			property._rotation._z -= cm_move * 4;
		}
		if (GameController::GetKey().IsKeyDown(DIK_D)){
			property._rotation._y += cm_move * 4;
		}
		else if (GameController::GetKey().IsKeyDown(DIK_A)){
			property._rotation._y -= cm_move * 4;
		}


	}
	else{
		if (GameController::GetKey().IsKeyDown(DIK_E)){
			property._rotation._y += cm_move * 4;
		}
		else if (GameController::GetKey().IsKeyDown(DIK_Q)){
			property._rotation._y -= cm_move * 4;
		}
		if (GameController::GetKey().IsKeyDown(DIK_A)){
			property._translation._x -= cm_move * cos(kAetherPI * property._rotation._y / 180);
			property._translation._z += cm_move * sin(kAetherPI * property._rotation._y / 180);
		}
		else if (GameController::GetKey().IsKeyDown(DIK_D)){
			property._translation._x += cm_move * cos(kAetherPI * property._rotation._y / 180);
			property._translation._z -= cm_move * sin(kAetherPI * property._rotation._y / 180);
		}
		if (GameController::GetKey().IsKeyDown(DIK_W)){
			property._translation._x += cm_move * sin(kAetherPI * property._rotation._y / 180);
			property._translation._z += cm_move * cos(kAetherPI * property._rotation._y / 180);
		}
		else if (GameController::GetKey().IsKeyDown(DIK_S)){
			property._translation._x -= cm_move * sin(kAetherPI * property._rotation._y / 180);
			property._translation._z -= cm_move * cos(kAetherPI * property._rotation._y / 180);
		}
		if (GameController::GetKey().IsKeyDown(DIK_SPACE)){
			property._translation._y += cm_move;
		}
		else if (GameController::GetKey().IsKeyDown(DIK_LSHIFT)){
			property._translation._y -= cm_move;
		}
	}


}
#endif
