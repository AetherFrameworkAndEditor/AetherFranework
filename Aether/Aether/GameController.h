#ifndef _GAMECONTROLLER_H
#define _GAMECONTROLLER_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameController.h
@brief     コントローラーを経由してマウスやキーボードへアクセスする。

*******************************************************************************
@date       2016/2/27
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/

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
		/*
		@brief          デバイスの初期化
		@param          インスタンスハンドル
		@param          ウィンドウハンドル
		@return         成功時 true / 失敗時 false
		@exception      none
		*/
		static bool Create(HINSTANCE&, HWND&);
		/*
		@brief          キーボードオブジェクトの取得
		@param          none
		@return         キーボードオブジェクト
		@exception      none
		*/
		static GameKeyBord& GetKey();
		/*
		@brief          マウスオブジェクトの取得
		@param          none
		@return         マウスオブジェクト
		@exception      none
		*/
		static GameMouse& GetMouse();

		/*
		@brief          デバイスの解放処理
		@param          none
		@return         none
		@exception      none
		*/
		static void Destroy();
		/*
		@brief          更新処理
		@param          none
		@return         成功時 true / 失敗時 false
		@exception      none
		*/
		static bool Frame();

	private:
		GameController();
		~GameController();
		/*
		@brief          デバイスの初期化
		@param          インスタンスハンドル
		@param          ウィンドウハンドル
		@return         成功時 true / 失敗時 false
		@exception      none
		*/
		static bool Initialize(HINSTANCE&, HWND&);

	private:
		static HWND m_hWnd;
	};
}
#endif