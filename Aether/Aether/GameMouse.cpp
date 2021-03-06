#include "GameMouse.h"
#include"ModelUtility.h"

using namespace aetherClass;


GameMouse::GameMouse()
{
	SecureZeroMemory(&m_screen, sizeof(POINT));
	SecureZeroMemory(&m_mousePoint, sizeof(POINT));
	m_directInput = nullptr;
	m_mouse= nullptr;

}


GameMouse::~GameMouse()
{
	SecureZeroMemory(&m_screen, sizeof(POINT));
	SecureZeroMemory(&m_mousePoint, sizeof(POINT));
}

bool GameMouse::Initialize(HINSTANCE& hInstance, HWND& hWnd){
	HRESULT result;
	m_hWnd = hWnd;

	Vector2 screen = aetherFunction::GetWindowSize(m_hWnd);
	m_screen = { screen._x,screen._y };


	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result)){ return false; }
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result)){ return false; }
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result)){ return false; }
	result = m_mouse->SetCooperativeLevel(m_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result)){ return false; }
	result = m_mouse->Acquire();
	if (FAILED(result)){ return false; }

}

void GameMouse::SetCursor(std::wstring file){
	static HCURSOR hCursor;
	DestroyCursor(hCursor);
	hCursor = LoadCursorFromFile(file.c_str());
	SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)hCursor);
	return;
}

bool GameMouse::Frame()
{
	bool result;


	result = Read();
	if (!result)
	{
		return false;
	}

	GetCursorPos(&m_mousePoint);
	ScreenToClient(m_hWnd, &m_mousePoint);

	return true;
}

bool GameMouse::Read()
{
	HRESULT result;

	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}

void GameMouse::Finalize()
{

	if (m_mouse)
	{
		 m_mouse->Unacquire();
		 m_mouse->Release();
		 m_mouse = nullptr;
	}

	if ( m_directInput)
	{
		 m_directInput->Release();
		 m_directInput = nullptr;
	}

	return;
}

bool GameMouse::IsLeftButtonDown()
{
	if (m_mouseState.rgbButtons[0] & 0x80)
	{
		return true;
	}
	return false;
}

bool GameMouse::IsRightButtonDown()
{
	if (m_mouseState.rgbButtons[1] & 0x80)
	{
		return true;
	}
	return false;
}

bool GameMouse::IsWheelDown()
{
	if (m_mouseState.rgbButtons[2] & 0x80)
	{
		return true;
	}
	return false;
}

bool GameMouse::IsLeftButtonTrigger()
{
	static bool prevState[sizeof(m_mouseState.rgbButtons) / sizeof(m_mouseState.rgbButtons[0])];
	bool current = m_mouseState.rgbButtons[0] & 0x80;
	bool ret = current && !prevState[0];
	prevState[0] = current;

	return ret;
}

bool GameMouse::IsRightButtonTrigger()
{
	static bool prevState[sizeof(m_mouseState.rgbButtons) / sizeof(m_mouseState.rgbButtons[1])];
	bool current = m_mouseState.rgbButtons[1] & 0x80;
	bool ret = current && !prevState[1];
	prevState[1] = current;

	return ret;
}

bool GameMouse::IsWheelTrigger()
{
	static bool prevState[sizeof(m_mouseState.rgbButtons) / sizeof(m_mouseState.rgbButtons[2])];
	bool current = m_mouseState.rgbButtons[2] & 0x80;
	bool ret = current && !prevState[2];
	prevState[2] = current;

	return ret;
}


RayVector GameMouse::Intersection(ViewCamera camera)
{
	float pointX, pointY;
	Matrix4x4 projectionMatrix, viewMatrix, worldMatrix, translateMatrix;
	Vector3 direction, origin;


	pointX = ((2.0f*(float)m_mousePoint.x) / (float)m_screen.x) - 1.0f;
	pointY = (((2.0f*(float)m_mousePoint.y) / (float)m_screen.y) - 1.0f)*-1.0f;


	projectionMatrix = GetDirect3DManager()->GetProjectionMatrix();

	pointX = pointX / projectionMatrix._11;
	pointY = pointY / projectionMatrix._22;

	viewMatrix = camera.GetViewMatrix();
	viewMatrix.Inverse();

	direction._x = (pointX * viewMatrix._11) + (pointY * viewMatrix._21) + viewMatrix._31;
	direction._y = (pointX * viewMatrix._12) + (pointY * viewMatrix._22) + viewMatrix._32;
	direction._z = (pointX * viewMatrix._13) + (pointY * viewMatrix._23) + viewMatrix._33;

	origin = camera.property._translation;


	translateMatrix.TranslateMatrix(origin);

	translateMatrix.Inverse();

	direction = direction.TransformCoordNormal(translateMatrix);

	RayVector ray;
	ray._direction = direction.Normalize();
	ray._origin = origin;
	ray._scaler = 1;

	return ray;
}

Vector2 GameMouse::GetMousePosition()
{
	return Vector2(m_mousePoint.x,m_mousePoint.y);
}

void GameMouse::ChangeActiveWindow(HWND hwnd){
	m_hWnd = hwnd;
	m_mouse->SetCooperativeLevel(m_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_mouse->Acquire();
}

float GameMouse::GetWheelMovement(){
	return m_mouseState.lZ;
}
Vector2 GameMouse::GetMouseMovement(){
	return Vector2(m_mouseState.lX,m_mouseState.lY);
}
