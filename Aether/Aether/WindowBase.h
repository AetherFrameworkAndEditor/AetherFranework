/******************************************************************************/
/*! @addtogroup aetherClass
@file      WindowBase.h
@brief     Window作成する際に基底クラスとして使用するクラス

*******************************************************************************
@date       2016/3/12
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/

#ifndef _WINDOWBASE_H
#define _WINDOWBASE_H

#include<Windows.h>
#include<string>
#include"Vector2.h"

namespace aetherClass{
	
	class WindowBase
	{
	public:
		/*
			拡張ウィンドウ等のスタイルを変更したい場合利用する
			SetWindowStyleをCreateより先に実行すること
			フラグの詳細はMicrosoftへ
		*/
		struct WindowStyleDesc
		{
			WindowStyleDesc(){
				_classStyle = CS_HREDRAW | CS_VREDRAW;
				_windowStyle = WS_OVERLAPPED | WS_SYSMENU;
				_windowStyleEx = WS_EX_APPWINDOW;
				_parent = NULL;
				_menu = NULL;
			}
			UINT _classStyle;
			DWORD _windowStyleEx, _windowStyle;
			HWND _parent;
			HMENU _menu;
		};
	public:
		WindowBase();
		~WindowBase();

		/*
		@brief          ウィンドウハンドルを得る
		@param          none
		@return         ウィンドウハンドル
		*/
		HWND GetWindowHandle();

		/*
		@brief          ウィンドウ名を得る
		@param          none
		@return         ウィンドウ名
		*/
		std::wstring GetWindowName();
	
		/*
		@breaf	拡張ウィンドウ等のスタイルを変更したい場合利用する
				SetWindowStyleをCreateより先に実行すること
				フラグの詳細はMicrosoftへ
		@param          WindowStyleDesc
		@return         none
		*/
		void SetWindowStyles(WindowBase::WindowStyleDesc windowStyleDesc);

		/*
		@brief          ウィンドウを生成する。
		@param          ウィンドウ名（識別子）
		@param          サイズ
		@param          表示位置
		@return         生成完了　true/失敗 false
		@exception		デバッグ時	ASSERT_Message
		*/
		bool Create(std::wstring windowName, Vector2 screenSize, Vector2 pos = { 0, 0 });

	private:

		BOOL RegisterWindow(std::wstring windowName);
		static LRESULT CALLBACK CloseWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		bool InitializeWindow(Vector2 screenSize, Vector2 screenPos);
		
		/*
		@brief          ウィンドウプロシージャ 継承した時に独自の処理を追加する
		@return         callback
		@exception		none
		*/
		virtual LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		/*
		@brief          ウィンドウ生成後の初期化処理
		@return         none
		@exception		none
		*/
		virtual void OnCreate(){};

	protected:
		HWND m_hWnd;
		std::wstring m_windowName;
		WindowStyleDesc	m_styleDesc;

	};

}

#endif