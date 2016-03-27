#ifndef _GAMEMOUSE_H
#define _GAMEMOUSE_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameMouse.h
@brief     マウスに関する処理

*******************************************************************************
@date       2016/2/28
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
#include"Line.h"
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
		/*
		@brief          デバイスの初期化
		@param          インスタンスハンドル
		@param          ウィンドウハンドル
		@return         成功時 true / 失敗時 false
		@exception      none
		*/
		bool Initialize(HINSTANCE&, HWND&);

		/*
		@brief          マウスや状態の更新
		@param          none
		@return         成功時 true / 失敗時 false
		@exception      none
		*/
		bool Frame();

		/*
		@brief          デバイス等の解放処理
		@param          none
		@return         none
		@exception      none
		*/
		void Finalize();

		/*
		@brief          カーソル画像を変えられる
		@param          ファイル名
		@return         none
		@exception      none
		*/
		void SetCursor(std::wstring);

		/*
		@brief          左クリックがされているか（長押し可）
		@param          none
		@return         true/false
		@exception      none
		*/
		bool IsLeftButtonDown();
		/*
		@brief          右クリックがされているか（長押し可）
		@param          none
		@return         true/false
		@exception      none
		*/
		bool IsRightButtonDown();
		/*
		@brief          中クリックがされているか（長押し可）
		@param          none
		@return         true/false
		@exception      none
		*/
		bool IsWheelDown();

		/*
		@brief          左クリックがされているか（１回のみ）
		@param          none
		@return         true/false
		@exception      none
		*/
		bool IsLeftButtonTrigger();
		/*
		@brief          右クリックがされているか（１回のみ）
		@param          none
		@return         true/false
		@exception      none
		*/
		bool IsRightButtonTrigger();
		/*
		@brief          中クリックがされているか（１回のみ）
		@param          none
		@return         true/false
		@exception      none
		*/
		bool IsWheelTrigger();

		/*
		@brief          マウス座標をワールドへ変換する処理を行う
		@param          ViewCamera
		@return         RayVector型の変数
		@exception      none
		*/
		RayVector Intersection(ViewCamera);
		/*
		@brief          コントローラーが反応するウィンドウを変更する
		@param          ウィンドウハンドル
		@return         none
		@exception      none
		*/
		void ChangeActiveWindow(HWND hwnd);
		/*
		@brief          ホイールの回転数を取得する
		@param          none
		@return         ホイール回転数
		@exception      none
		*/
		float GetWheelMovement();
		/*
		@brief          マウスの移動量を取得する（座標ではない）
		@param          none
		@return         マウスの移動量
		@exception      none
		*/
		Vector2 GetMouseMovement();
		/*
		@brief          マウスの画面座標を取得する
		@param          none
		@return         マウスの座標
		@exception      none
		*/
		Vector2 GetMousePosition();

	private:
		/*
		@brief          更新処理
		@param          none
		@return         成功時 true/失敗時 false
		@exception      none
		*/
		bool Read();

	private:
		HWND m_hWnd;
		IDirectInput8* m_directInput;
		IDirectInputDevice8* m_mouse;

		DIMOUSESTATE m_mouseState;

		POINT m_screen;
		POINT m_mousePoint;

	};
}
#endif