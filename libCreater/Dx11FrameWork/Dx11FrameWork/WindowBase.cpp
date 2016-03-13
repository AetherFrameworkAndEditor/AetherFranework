#include "WindowBase.h"

using namespace aetherClass;
WindowBase::WindowBase()
{
	m_hWnd = nullptr;
}


WindowBase::~WindowBase()
{
	DestroyWindow(m_hWnd);
	UnregisterClass(m_windowName.c_str(), GetModuleHandle(NULL));

}


BOOL WindowBase::RegisterWindow(std::wstring windowName)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.style = m_styleDesc._classStyle;
	wc.lpfnWndProc = CloseWindowProcedure;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = windowName.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);

	// ウインドウクラスの登録
	if (!RegisterClassEx(&wc)) return FALSE;
}


LRESULT CALLBACK WindowBase::CloseWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	WindowBase* instance = (WindowBase*)GetWindowLong(hWnd, GWL_USERDATA);
	if (instance){
		return instance->WindowProcedure(hWnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}


LRESULT CALLBACK WindowBase::WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch (uMsg)
	{
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return S_OK;
}


HWND WindowBase::GetWindowHandle(){
	return m_hWnd;
}
bool WindowBase::Create(std::wstring windowName, Vector2 screenSize, Vector2 screenPos){
	bool result;
	m_windowName = windowName;
	result = this->RegisterWindow(m_windowName);
	if (!result){
		_ASSERT_EXPR(false, "Couldnot registered window");
		return false;
	}
	result=this->InitializeWindow(screenSize, screenPos);
	if (!result){
		_ASSERT_EXPR(false, "Couldnot Create window");
		return false;
	}


}


bool WindowBase::InitializeWindow(Vector2 screenSize, Vector2 screenPos){
	POINT screen = { (int)screenSize._x, (int)screenSize._y };
	Vector2 position;
	if (screenPos._x == 0 && screenPos._y == 0){
		position._x = (::GetSystemMetrics(SM_CXSCREEN) - screen.x) / 2;
		position._y = (::GetSystemMetrics(SM_CYSCREEN) - screen.y) / 2;
	}
	else{
		position._x = screenPos._x;
		position._y = screenPos._y;
	}


	m_hWnd = CreateWindowEx(m_styleDesc._windowStyleEx, m_windowName.c_str(), m_windowName.c_str(),
		m_styleDesc._windowStyle,
		position._x, position._y,
		(screen.x) + (GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(screen.y) + (GetSystemMetrics(SM_CXDLGFRAME) * 2),
		m_styleDesc._parent, m_styleDesc._menu, GetModuleHandle(NULL), NULL);
	if (!m_hWnd){
		return false;
	}
	// Bring the window up on the screen and set it as main focus
	::ShowWindow(m_hWnd, SW_SHOW);

	SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this);

	this->OnCreate();

	return true;

}


void WindowBase::SetWindowStyles(WindowBase::WindowStyleDesc desc){
	m_styleDesc = desc;
}

std::wstring WindowBase::GetWindowName(){
	return m_windowName;
}
