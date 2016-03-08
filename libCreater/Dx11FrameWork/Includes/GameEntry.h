/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameEntry.h
@brief     エントリーポイント作成用クラス

*******************************************************************************
@date       2016/01/06 23:06
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/01/06 23:06 橋本航
-# Initial Version
- 2016/01/12 10:07 橋本航
-# remove IsEnd function
******************************************************************************/
#ifndef _GAMEENTRY_H
#define _GAMEENTRY_H
#include "ConsoleWindow.h"
#include "GameFrame.h"
#include <memory>
#include <string>
#include <Windows.h>
namespace aetherClass{

	namespace{
		const LPCWSTR kWindowName = L"AetherFrameWork";
		const int kWindowWidth = 800;
		const int kWindowHeight = 600;
	}

	class GameEntry
	{
	public:
		GameEntry();
		~GameEntry();
	
		/*
		@brief          初期化用
		@param[in]      フルスクリーン true/ウィンドウモード false    default[false]
		@param[in]      ウィンドウの名前    default[kWindowName]
		@param[in]      ウィンドウの幅    default[kWindowWidth]
		@param[in]      ウィンドウの高さ    default[kWindowHeight]
		@return         成功時：true/失敗時: false
		@exception      none
		*/
		virtual bool Initialize(
			const bool isFullScreen = false,
			LPCWSTR windowName = kWindowName, 
			const int width = kWindowWidth,
			const int height = kWindowHeight)final;
		
		/*
		@brief          解放用
		@param[in]      none
		@return         none
		@exception      none
		*/
		virtual void Finalize()final;


		/*
		@brief          メインループ。SetFrameObjectで設定されたGameFrameクラスのFrame関数が実行される
		@param          none
		@return         成功時：true/失敗時: false
		@exception      none
		*/
		virtual void GameRun()final;

		/*
		@brief          メッセージハンドラー。キーの受け取り
		@param[in]      ウィンドウハンドラ
		@param[in]      メッセージ
		@param[in]      wParam
		@param[in]      lParam
		@return         成功時：true/失敗時: false
		@exception      none
		*/
		virtual LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM)final;

		/*
		@brief          GameFrame型を継承した独自クラスを保存。
		                引数で渡されたGameFrame型オブジェクトのFrameRunningBuffer関数が実際のメイン部になる
		@param[in]      独自に実装したGameFrameを継承したクラスを渡す
		@return         none
		@exception      none
		*/
		virtual void SetGameFrame(GameFrame*)final;

		/*
		@brief          ウィンドウのハンドル情報取得用
		@param          none
		@return         HWND型オブジェクト
		@exception      none
		*/
		const HWND* GetWindowHandle();

	private:

		/*
		@brief          ウィンドウの初期化用
		@param[in]      フルスクリーン： true/ウィンドウモード： false
		@return         POINT型にスクリーンの幅と高さを取得した変数
		@exception      none
		*/
		virtual POINT InitalizeWindow(const bool isFull, LPCWSTR windowName)final;

		/*
		@brief          初期化用.オーバーライドすることで独自処理を実装できる 
		@param[in]      none
		@return         成功時：true/失敗時: false
		@exception      none
		*/
		virtual bool InitializeBuffer(){ return true; };

		/*
		@brief          解放用.オーバーライドすることで独自処理を実装できる
		@param[in]      none
		@return         成功時：true/失敗時: false
		@exception      none
		*/
		virtual void FinalizationBuffer(){ return; };

	private:
		// GameFrameオブジェクトのアドレス保存用
		static GameFrame* m_frame;

		unsigned int m_windowWidth;
		unsigned int m_windowHeight;

		
		LPCWSTR m_windowName;
		HINSTANCE m_hInstance;
		HWND m_hWnd;
	};

	
}

#endif