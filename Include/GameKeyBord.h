/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameKeyBord.h
@brief     キー入力管理クラス

*******************************************************************************
@date       2016/02/03
@author     橋本　航
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/02/03 橋本　航
-# Initial Version

******************************************************************************/
#ifndef _GAMEKEYBORD_H
#define _GAMEKEYBORD_H
#include<dinput.h>

#ifndef _CONTROLLER_
#define _CONTROLLER_
#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#endif

namespace aetherClass{
	class GameKeyBord
	{
	public:
		GameKeyBord();
		~GameKeyBord();

		bool Initialize(HINSTANCE,HWND);
		bool Read();
		bool IsKeyDown(unsigned int keyType);
		void Finalize();
		void ChangeActiveWindow(HWND hwnd);

	private:
		IDirectInput8* m_directInput;
		IDirectInputDevice8* m_keybord;
		unsigned char m_keybordState[256];
	};
}
#endif