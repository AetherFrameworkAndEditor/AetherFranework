/******************************************************************************/
/*! @addtogroup aetherClass
@file      AetherWindow.h
@brief     WindowBase����h��������{�E�B���h�E�N���X�B

*******************************************************************************
@date       2016/3/12
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/

#ifndef _AETEHRWINDOW_H
#define _AETEHRWINDOW_H

#include "WindowBase.h"
namespace aetherClass{
	class AetherWindow :
		public WindowBase
	{
	public:
		AetherWindow();
		~AetherWindow();
		LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	};

}
#endif