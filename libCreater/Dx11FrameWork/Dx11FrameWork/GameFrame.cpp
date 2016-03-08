#include "GameFrame.h"
#include "NullScene.h"
#include <assert.h>
#include <iostream>
using namespace aetherClass;

std::unique_ptr<Direct3DManager> GameFrame::m_direct3D = nullptr;
Color GameFrame::m_backgroundColor = Color(NULL, NULL, NULL, NULL);

std::unique_ptr<GameSceneManager> GameFrame::m_sceneManager = nullptr;
std::unique_ptr<GameScene> GameFrame::m_scene = nullptr;;
GameFrame::GameFrame(){}

//
bool GameFrame::Initialize(HWND hWnd,POINT size, const bool isFull, const float screenDepth, const float screenNear){
	bool result;

	m_direct3D = std::make_unique<Direct3DManager>();
	if (!m_direct3D)
	{
		return false;
	}

	POINT screen = { 800, 600 };

	result = m_direct3D->Initialize(screen, kVsyncEnabled, hWnd, isFull, screenDepth, screenNear);
	if (!result)
	{
		return false;
	}

	m_sceneManager = std::make_unique<GameSceneManager>();

	m_scene = std::make_unique<NullScene>();

	// Nullオブジェクトをセット
	GameSceneManager::SetCurrentScene(m_scene.get());

	// user's override process
	result = InitializeBuffer();

	if (!result)
	{
		assert(!"不正な処理です.class:GameFrame child class. function name:InitializeBuffer()");
		return false;
	}
	return true;
}

// 実際のメインループ
bool GameFrame::FrameRunning(){
	bool result = true;

	m_direct3D->BeginScene(m_backgroundColor);
	// user's override process
	result = FrameRunningBuffer();

	result = m_sceneManager->SceneInitialize();
	if (!result)
	{
		assert(!"do not Initialize");
		return false;
	}

	result = m_sceneManager->SceneUpdatar();
	
	m_sceneManager->SceneRender();
	
	// UIだけ2Dモードで描画
	m_entity.GetDirect3DManager()->Change2DMode();
	m_sceneManager->SceneUIRender();
	m_entity.GetDirect3DManager()->Change3DMode();

	m_sceneManager->ChangeScene();
	
	m_direct3D->EndScene();

	return result;
}

// 解放処理
void GameFrame::Finalize(){

	// user's override process
	FinalizeBuffer();

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