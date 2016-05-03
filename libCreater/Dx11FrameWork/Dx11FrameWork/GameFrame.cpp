#include "GameFrame.h"
#include "NullScene.h"
#include"ModelUtility.h"
#include "GameClock.h"
#include <assert.h>
#include <iostream>
#include "GameScene.h"
using namespace aetherClass;

Color GameFrame::m_backgroundColor = Color(NULL, NULL, NULL, NULL);
GameFrame::GameFrame(){}

//
bool GameFrame::Initialize(WindowBase **window ,UINT numWindow, const float screenDepth, const float screenNear){
	bool result;

	m_direct3D = std::make_unique<Direct3DManager>();
	if (!m_direct3D){
		return false;
	}

	Vector2 screenSize = aetherFunction::GetWindowSize(window[0]->GetWindowHandle());
	result = m_direct3D->Initialize(screenSize, kVsyncEnabled, window,numWindow, false, screenDepth, screenNear);
	if (!result){
		return false;
	}
	HINSTANCE hInstance = GetModuleHandle(NULL);
	HWND hwnd = window[0]->GetWindowHandle();
	GameController::Create(hInstance, hwnd);

	m_sceneManager = std::make_unique<GameSceneManager>();

	m_scene = std::make_unique<NullScene>();

	// Null�I�u�W�F�N�g���Z�b�g
	GameSceneManager::SetCurrentScene(m_scene.get());

	// user's override process
	result = InitializeBuffer();

	if (!result)
	{
		assert(!"�s���ȏ����ł�.class:GameFrame child class. function name:InitializeBuffer()");
		return false;
	}
	
	return true;
}

void GameFrame::GameRun(){
	MSG msg;
	bool isEnd, result;

	SecureZeroMemory(&msg, sizeof(MSG));

	isEnd = false;

	while (!isEnd)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			isEnd = true;
		}
		else
		{
			GameController::Frame();
			result = FrameRunning();

			if (!result)
			{
				isEnd = true;
			}
		}
	}

	// Exit application
	return;
}

// ���ۂ̃��C�����[�v
bool GameFrame::FrameRunning(){

	// ���Ԃ̎擾
	GameClock::BeginTime();

	bool result = true;

	m_direct3D->BeginScene(m_backgroundColor);
	// user's override process
	result = FrameRunningBuffer();
	if (!result)
	{
		return false;
	}
	
	result = m_sceneManager->SceneInitialize();
	if (!result)
	{
		assert(!"do not Initialize");
		return false;
	}
	
	result = m_sceneManager->SceneUpdatar();

	m_sceneManager->SceneRender();

	// UI����2D���[�h�ŕ`��
	m_entity.GetDirect3DManager()->Change2DMode();
	m_sceneManager->SceneUIRender();
	m_entity.GetDirect3DManager()->Change3DMode();

	m_sceneManager->ChangeScene();

	m_direct3D->EndScene();

	// ���Ԃ̌v�Z���s��deltaTime�����߂�
	GameClock::EndTime();

	return result;
}

// �������
void GameFrame::Finalize(){

	// user's override process
	FinalizeBuffer();
	if (m_scene){
		m_scene.release();
		m_scene = nullptr;
	}
	if (m_sceneManager)
	{
		m_sceneManager.release();
		m_sceneManager = nullptr;
	}
	
	GameController::Destroy();

	if (m_direct3D)
	{
		m_direct3D->Finalize();
		m_direct3D.release();
		m_direct3D = nullptr;
	}

	m_backgroundColor = Color(NULL, NULL, NULL , NULL);
	return;
}

//
void GameFrame::BackgroundColor(Color color){
	m_backgroundColor = color;
}