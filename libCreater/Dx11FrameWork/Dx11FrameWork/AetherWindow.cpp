#include "AetherWindow.h"
#include"GameController.h"
using namespace aetherClass;
AetherWindow::AetherWindow()
{
}


AetherWindow::~AetherWindow()
{
}

LRESULT CALLBACK AetherWindow::WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	UINT flg = LOWORD(wParam);
	switch (uMsg)
	{
	case WM_ACTIVATE:
		if (flg  == WA_ACTIVE || flg == WA_CLICKACTIVE){
			GameController::GetMouse().ChangeActiveWindow(m_hWnd);
			break;
		}
	case WM_KEYDOWN:
		{
			GameController::GetKey().KeyDown((unsigned int)wParam);

			break;
		}
		case WM_KEYUP:
		{
			GameController::GetKey().KeyUp((unsigned int)wParam);
			break;
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);

			break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return S_OK;
}
