#ifndef _DIRECTXENTITY_H
#define _DIRECTXENTITY_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      DirectXEntity.h
@brief     Direct3Dのアドレスを保持
           描画するオブジェクトなどはこのクラスを継承する

*******************************************************************************
@date       2015/12/23
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/23 橋本航
-# Initial Version
******************************************************************************/
#include "Direct3DManager.h"
namespace aetherClass{
	class DirectXEntity
	{
		public:
			DirectXEntity();
			~DirectXEntity();
		

			/*
			@brief          Direct3DManagerのアドレスをコピーし保持
			@param[in]      manager Direct3DManager型のポインタ
			@param[in]      適用するウィンドウハンドル
			@return         none
			@exception      none
			*/
			static void CopyDirectX(Direct3DManager* manager,const HWND);

			/*
			@brief          Direct3DManagerの参照を返す
			@param[in]      manager Direct3DManager型のポインタ
			@par            Refer
			- 参照するメンバ変数   m_direct3d
			@par            Modify
			- 変更するメンバ変数   none
			@return         none
			@exception      none
			*/
			Direct3DManager* GetDirect3DManager()const;


			/*
			@brief          ウィンドウハンドルの参照を返す
			@param[in]      none
			@return         HWND
			@exception      none
			*/
			HWND& GetWindowHandle()const;


		private:
			static Direct3DManager* m_direct3d;
			static HWND m_hWnd;
	};
}
#endif