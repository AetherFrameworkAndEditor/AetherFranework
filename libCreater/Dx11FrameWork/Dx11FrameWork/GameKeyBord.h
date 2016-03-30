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
#include <Windows.h>

namespace{
	const int kMaxKeyType = 256;
}
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
		void Initialize();
		
		/*
		@brief          キーが押されたか
		@param          キーコード
		@return         true/false
		@exception      none
		*/
		bool IsKeyDown(unsigned int);
		

		/*
		@brief          キーが押されているか
		@param          キーコード
		*/
		void KeyDown(unsigned int keyType);

		/*
		@brief          キーが押されて離されたか
		@param          キーコード
		@exception      none
		*/
		void KeyUp(unsigned int keyType);
	private:
		bool m_keybordState[256];
	};
}
#endif