/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameKeyBord.h
@brief     キー入力管理クラス

*******************************************************************************
@date       2016/2/27
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu
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

		/*
		@brief          デバイスの初期化
		@param          インスタンスハンドル
		@param          ウィンドウハンドル
		@return         成功時 true / 失敗時 false
		@exception      none
		*/
		bool Initialize(HINSTANCE, HWND);
		/*
		@brief          更新処理
		@param          none
		@return         成功時 true/失敗時 false
		@exception      none
		*/
		bool Read();
		/*
		@brief          キーが押されているか
		@param          DIK_系のキーコード
		@return         true/false
		@exception      none
		*/
		bool IsKeyDown(unsigned int keyType);
		/*
		@brief          デバイス等の解放処理
		@param          none
		@return         none
		@exception      none
		*/
		void Finalize();
		/*
		@brief          コントローラーが反応するウィンドウを変更する
		@param          ウィンドウハンドル
		@return         none
		@exception      none
		*/
		void ChangeActiveWindow(HWND hwnd);

	private:
		IDirectInput8* m_directInput;
		IDirectInputDevice8* m_keybord;
		unsigned char m_keybordState[256];
	};
}
#endif