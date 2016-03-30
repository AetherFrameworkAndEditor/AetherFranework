#include "GameController.h"

using namespace aetherClass;
HWND GameController::m_hWnd = NULL;
GameController::GameController()
{
}

GameController::~GameController()
{
}

bool GameController::Create(HINSTANCE& hInstance, HWND& hWnd){
	bool result;
	result=Initialize(hInstance, hWnd);
	return result;
}

//
bool GameController::Initialize(HINSTANCE& hInstance, HWND& hWnd)
{
	HRESULT result;
	m_hWnd = hWnd;
	GetKey().Initialize();
	result = GetMouse().Initialize(hInstance, hWnd);

	return result;
}

//
GameKeyBord& GameController::GetKey(){
	static GameKeyBord key;
	return key;
}

GameMouse& GameController::GetMouse(){
	static GameMouse mouse;
	return mouse;
}

//
bool GameController::Frame()
{
	bool result;

	result = GetMouse().Frame();
	if (!result){
		return false;
	}

	return true;
}


void GameController::Destroy()
{
	GetMouse().Finalize();
	return;
}
