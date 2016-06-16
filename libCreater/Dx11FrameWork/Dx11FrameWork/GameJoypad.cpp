#include "GameJoypad.h"
#include <iostream>
#include <Windows.h>
#include <XInput.h>
#pragma comment(lib, "Xinput.lib")
using namespace aetherClass;
#define Threshold   65535 / 4 //しきい値
GameJoypad::GameJoypad()
{
}


GameJoypad::~GameJoypad()
{
}


bool GameJoypad::Initialize(){
	// キーの初期化
	m_buttonList.insert(std::make_pair(eJoyButton::eUp, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eDown, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eLeft, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eRight, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eRUp, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eRDown, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eRLeft, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eRRight, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eA, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eB, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eX, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eY, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eLB1, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eRB1, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eStart, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eBack, false));
	m_buttonList.insert(std::make_pair(eJoyButton::eNull, false));

	m_prevButtonList = m_buttonList;
	return true;
}

void GameJoypad::ReadKey(){
	// パッドが繋がってなかったら無視
	XINPUT_STATE inputState;

	SecureZeroMemory(&inputState, sizeof(XINPUT_STATE));

	//	system("cls");

	if (XInputGetState(JOYSTICKID1, &inputState) != ERROR_SUCCESS){
		return;
	}

	// 前回の状態を書き換える
	m_prevButtonList = m_buttonList;
	WORD button = inputState.Gamepad.wButtons;
	SHORT stictLX = inputState.Gamepad.sThumbLX;
	SHORT stictLY = inputState.Gamepad.sThumbLY;
	SHORT sticRX = inputState.Gamepad.sThumbRX;
	SHORT stictRY = inputState.Gamepad.sThumbRY;
	// ↑
	if (button&XINPUT_GAMEPAD_DPAD_UP || stictLY>Threshold){
		m_buttonList[eJoyButton::eUp] = true;
	}
	else{
		m_buttonList[eJoyButton::eUp] = false;
	}

	// ↓
	if (button&XINPUT_GAMEPAD_DPAD_DOWN || stictLY<-Threshold){
		m_buttonList[eJoyButton::eDown] = true;
	}
	else{
		m_buttonList[eJoyButton::eDown] = false;
	}

	// →
	if (button&XINPUT_GAMEPAD_DPAD_RIGHT || stictLX>Threshold){
		m_buttonList[eJoyButton::eRight] = true;
	}
	else{
		m_buttonList[eJoyButton::eRight] = false;
	}

	// ←
	if (button&XINPUT_GAMEPAD_DPAD_LEFT || stictLX<-Threshold){
		m_buttonList[eJoyButton::eLeft] = true;
	}
	else{
		m_buttonList[eJoyButton::eLeft] = false;
	}

	// 右スティック
	// ↑
	if (stictRY>XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE){
		m_buttonList[eJoyButton::eRUp] = true;
	}
	else{
		m_buttonList[eJoyButton::eRUp] = false;
	}

	// ↓
	if (stictRY<-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE){
		m_buttonList[eJoyButton::eRDown] = true;
	}
	else{
		m_buttonList[eJoyButton::eRDown] = false;
	}

	// →
	if (sticRX>XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE){
		m_buttonList[eJoyButton::eRRight] = true;
	}
	else{
		m_buttonList[eJoyButton::eRRight] = false;
	}

	// ←
	if (sticRX<-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE){
		m_buttonList[eJoyButton::eRLeft] = true;
	}
	else{
		m_buttonList[eJoyButton::eRLeft] = false;
	}

	// Aボタン
	if (button&XINPUT_GAMEPAD_A){

		m_buttonList[eJoyButton::eA] = true;
	}
	else{
		m_buttonList[eJoyButton::eA] = false;
	}

	// Bボタン
	if (button&XINPUT_GAMEPAD_B){
		m_buttonList[eJoyButton::eB] = true;
	}
	else{
		m_buttonList[eJoyButton::eB] = false;
	}

	// Xボタン
	if (button&XINPUT_GAMEPAD_X){
		m_buttonList[eJoyButton::eX] = true;
	}
	else{
		m_buttonList[eJoyButton::eX] = false;
	}

	// Yボタン
	if (button&XINPUT_GAMEPAD_Y){
		m_buttonList[eJoyButton::eY] = true;
	}
	else{
		m_buttonList[eJoyButton::eY] = false;
	}

	// LB1ボタン
	if (button&XINPUT_GAMEPAD_LEFT_SHOULDER){
		m_buttonList[eJoyButton::eLB1] = true;
	}
	else{
		m_buttonList[eJoyButton::eLB1] = false;
	}

	// RB1ボタン
	if (button&XINPUT_GAMEPAD_RIGHT_SHOULDER){
		m_buttonList[eJoyButton::eRB1] = true;
	}
	else{
		m_buttonList[eJoyButton::eRB1] = false;
	}

	// Startボタン
	if (button&XINPUT_GAMEPAD_START){
		m_buttonList[eJoyButton::eStart] = true;
	}
	else{
		m_buttonList[eJoyButton::eStart] = false;
	}

	// Backボタン
	if (button&XINPUT_GAMEPAD_BACK){
		m_buttonList[eJoyButton::eBack] = true;
	}
	else{
		m_buttonList[eJoyButton::eBack] = false;
	}
}

//　押している間
bool GameJoypad::IsButtonDown(eJoyButton button){
	return m_buttonList[button];
}

// 押した瞬間
bool GameJoypad::ButtonPress(eJoyButton button){
	if (m_buttonList[button] &&
		m_prevButtonList[button] != m_buttonList[button]){

		m_prevButtonList[button] = m_buttonList[button];
		return true;
	}
	return false;
}

// 押して離したとき
bool GameJoypad::ButtonRelease(eJoyButton button){
	if (!m_buttonList[button] &&
		m_prevButtonList[button] != m_buttonList[button]){

		m_prevButtonList[button] = m_buttonList[button];
		return true;
	}
	return false;
}

void GameJoypad::SetVibration(std::pair<unsigned int, unsigned int> vib){
	XINPUT_VIBRATION vibration;
	SecureZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = vib.first;
	vibration.wRightMotorSpeed = vib.second;
	XInputSetState(JOYSTICKID1, &vibration);
}

