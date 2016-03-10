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