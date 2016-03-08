#ifndef _GAMECONTROLLER_H
#define _GAMECONTROLLER_H
#define DIRECTINPUT_VERSION 0x0800

#include "DirectXEntity.h"
#include "Vector3.h"
#include <Windows.h>
#include <memory>
#include "ViewCamera.h"
#include "GameKeyBord.h"
#include"GameMouse.h"
namespace aetherClass{
	class GameController
	{

	public:
		
		static bool Create(HINSTANCE&, HWND&);
		static GameKeyBord& GetKey();
		static GameMouse& GetMouse();

		static void Destroy();
		static bool Frame();

	private:
		GameController();
		~GameController();

		static bool Initialize(HINSTANCE&, HWND&);

	private:
		static HWND m_hWnd;
	};
}
#endif