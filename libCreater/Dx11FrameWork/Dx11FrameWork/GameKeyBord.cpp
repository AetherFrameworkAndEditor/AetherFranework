#include "GameKeyBord.h"

using namespace aetherClass;
GameKeyBord::GameKeyBord()
{
	m_directInput = nullptr;
	m_keybord = nullptr;
}


GameKeyBord::~GameKeyBord()
{
}

//
bool GameKeyBord::Initialize(HINSTANCE hInstance, HWND hWnd){
	
	HRESULT result;
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result)){ return false; }
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keybord, NULL);
	if (FAILED(result)){ return false; }
	result = m_keybord->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result)){ return false; }
	result = m_keybord->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result)){ return false; }
	result = m_keybord->Acquire();
	if (FAILED(result)){ return false; }

	return result;
}

//
bool GameKeyBord::Read()
{
	HRESULT result;

	result = m_keybord->GetDeviceState(sizeof(m_keybordState), (LPVOID)&m_keybordState);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keybord->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool GameKeyBord::IsKeyDown(unsigned int keyType)
{
	if (m_keybordState[keyType] & 0x80)
	{
		return true;
	}
	return false;
}

void GameKeyBord::Finalize(){
	if (m_keybord)
	{
		m_keybord->Unacquire();
		m_keybord->Release();
		m_keybord = 0;
	}

	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}
}

void GameKeyBord::ChangeActiveWindow(HWND hwnd){
	m_keybord->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_keybord->Acquire();
}