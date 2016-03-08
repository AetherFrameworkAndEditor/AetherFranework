#ifndef _GAMEMOUSE_H
#define _GAMEMOUSE_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameMouse.h
@brief     マウスに関する処理

*******************************************************************************
@date       2016/2/3
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************/
#include"DirectXEntity.h"
#include<dinput.h>
#include"ViewCamera.h"
#include"Vector3.h"
#include<string>

#ifndef _CONTROLLER_
#define _CONTROLLER_
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#endif
namespace aetherClass{
	class GameMouse 
		: private DirectXEntity
	{
	public:
		GameMouse();
		~GameMouse();

	public:
		bool Initialize(HINSTANCE&, HWND&);
		bool Frame();
		void Finalize();

		void SetCursor(std::wstring);

		bool IsLeftButtonDown();
		bool IsRightButtonDown();
		bool IsWheelDown();

		bool IsLeftButtonTrigger();
		bool IsRightButtonTrigger();
		bool IsWheelTrigger();

		void Intersection(ViewCamera);

		Vector3 GetDirection();
		Vector3 GetOrigin();
		POINT GetMousePosition();
	private:
		bool Read();
		void ProcessInput();

	private:
		HWND m_hWnd;
		IDirectInput8* m_directInput;
		IDirectInputDevice8* m_mouse;

		DIMOUSESTATE m_mouseState;

		POINT m_mousePos;
		POINT m_screen;

		POINT m_mousePoint;

		Vector3 m_rayOrigin;
		Vector3 m_rayDirection;
	};
}
#endif