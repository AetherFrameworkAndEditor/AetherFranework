#include "GameSceneManager.h"
#include "GameScene.h"
#include "NullLoadScreen.h"
#include "NullScene.h"
#include <assert.h>
#include <iostream>
using namespace aetherClass;

std::unordered_map<std::string, GameScene*> GameSceneManager::m_scenesMap;

/*	Nullオブジェクトで初期化*/
GameScene* GameSceneManager::m_currentScene = new NullScene();
LoadScreen* GameSceneManager::m_loadObject = new NullLoadScreen();

/*	ステートの初期化	*/
GameSceneManager::eGameState GameSceneManager::m_gameState = GameSceneManager::eGameState::eNone;
GameSceneManager::eTransitionState GameSceneManager::m_transitionState = GameSceneManager::eTransitionState::eNone;

/*	それぞれの名前の初期化	*/
std::string GameSceneManager::m_nextSceneName = "None";
std::string GameSceneManager::m_currentSceneName = "None";

/*	フラグ関連	*/
bool GameSceneManager::m_isLoadScene = false;
bool GameSceneManager::m_isChangeScene = false;
LoadWaitState GameSceneManager::m_useLoadWaitRun = LoadWaitState::eNull;
LoadState GameSceneManager::m_useLoadScreen= LoadState::eNull;
GameActorManager GameSceneManager::m_actorManager;

GameSceneManager::GameSceneManager(){
	m_isChangeScene = false;
}
GameSceneManager::~GameSceneManager(){
	Finalize();
}

// 登録処理
void GameSceneManager::RegisterScene(GameScene* registerScene){
	// 登録済みなら何もしない
	if (FindScene(registerScene->GetName())) return;

	m_scenesMap.insert(std::make_pair(registerScene->GetName(), registerScene));
}

// 検索用
GameScene* GameSceneManager::FindScene(std::string name){
	auto findMap = m_scenesMap.find(name);
	if (findMap == m_scenesMap.end()) return nullptr;
	
	return findMap->second;
}

// シーンの初期化処理
bool GameSceneManager::SceneInitialize(){
	if (m_gameState != eGameState::eInitialize) return true;
	
	m_currentScene->Initialize();

	m_gameState = eGameState::eRender;

	return true;
}

// シーンの描画処理
void GameSceneManager::SceneRender(){
	if (m_gameState != eGameState::eRender)return;
	
	m_currentScene->Render();

	m_gameState = eGameState::eUIRender;
	return;
}

// シーンの描画処理
void GameSceneManager::SceneUIRender(){
	if (m_gameState != eGameState::eUIRender) return;
	
	m_currentScene->UIRender();

	m_gameState = eGameState::eUpData;
	return;
}

// シーンの更新処理
bool GameSceneManager::SceneUpdatar(){
	if (m_gameState != eGameState::eUpData) return true;
	
	bool result;
	result = m_currentScene->Updater();

	// 全オブジェクトの衝突判定検索
	m_actorManager.Collide();

	m_gameState = eGameState::eRender;
	return result;
}

// シーンの解放処理
void GameSceneManager::SceneFinalize(){
	if (m_gameState != eGameState::eFinalize) return;
	
	m_currentScene->Finalize();
	m_actorManager.RemoveChild();
	m_gameState = eGameState::eChange;
	return;
}


// 解放処理
void GameSceneManager::Finalize(){
	if (m_currentScene)
	{
		m_currentScene->Finalize();
		delete m_currentScene;
		m_currentScene = nullptr;
	}

	if (m_loadObject)
	{
		m_loadObject->Finalize();
		delete m_loadObject;
		m_loadObject = nullptr;
	}

	/*	ステートの初期化	*/
	m_gameState = GameSceneManager::eGameState::eNone;
	m_transitionState = GameSceneManager::eTransitionState::eNone;

	/*	それぞれの名前の初期化	*/
	m_nextSceneName = "None";

	// フラグの初期化
	m_isChangeScene = false;
	m_isLoadScene = false;

	m_actorManager.RemoveChild();

	for (auto index : m_scenesMap)
	{
		if (index.second)
		{
			if (index.second)
			{
				index.second->Finalize();
				delete index.second;
				index.second = nullptr;
			}
			
		}
	}

	m_scenesMap.clear();
}

//
void GameSceneManager::ChangeCurrentScene(){
	if (m_gameState != eGameState::eChange) return;

	delete m_currentScene;
	auto prevScene = m_scenesMap.find(m_currentSceneName);

	// 存在していたら配列から削除
	if (prevScene != m_scenesMap.end())
	{
		m_scenesMap.erase(prevScene);
	}
	m_currentScene = FindScene(m_nextSceneName);

	// 正常に入ってるかチェック
	if (!m_currentScene)
	{
		assert(!"not find next scene");
		return;
	}

	m_currentSceneName = m_currentScene->GetName();

	m_isLoadScene = true;
	m_gameState = eGameState::eNone;
	m_isCreateThread = false;
	m_isEndInitialize = false;
	return;
}


// カレントを次に移動するシーンに変える
void GameSceneManager::ChangeScene(){
	
	if (!m_isChangeScene) return;

	// トランジション始まり
	m_isTransitionInEnd = SceneTransitionIn();
	
	// まだ終わってない
	if (!m_isTransitionInEnd) return;
	
	// 解放処理
	SceneFinalize();

	// 使うシーンの入れ替え
	ChangeCurrentScene();

	// TODO: ロードと初期化を並列化
	if (!LoadScene())
	{
		return;
	}

	// ロードの待機処理
	if (!LaodWaitRun())
	{
		return;
	}

	// トランジションの呼び出し
	m_isTransitionOutEnd = SceneTransitionOut();

	if (!m_isTransitionOutEnd) return;
	
	return;
}

// トランジション効果IN
bool GameSceneManager::SceneTransitionIn(){
	if (m_transitionState != eTransitionState::eIn) return true;
	
	bool result = false;
	
	result = m_currentScene->TransitionIn();

	// in処理をしながら描画するため
	SceneRender();

	if (!result) return false;
	
	// ステートの変更
	m_gameState = eGameState::eFinalize;
	m_transitionState = eTransitionState::eOut;
	m_isLoadWaitEnd = false;
	return true;
}

// トランジション効果OUT
bool GameSceneManager::SceneTransitionOut(){
	if (m_transitionState != eTransitionState::eOut) return true;
	
	bool result = false;
	m_gameState = eGameState::eRender;
	result = m_currentScene->TransitionOut();
	// out処理をしながら描画するため
	SceneRender();

	if (!result) return false;
	
	m_gameState = eGameState::eRender;
	m_transitionState = eTransitionState::eNone;
	m_isChangeScene = false;
	return true;
}

// カレントシーンの登録
void GameSceneManager::SetCurrentScene(GameScene* scene){
	m_currentScene = scene;
	m_gameState = eGameState::eInitialize;
	m_currentSceneName = m_currentScene->GetName();
}

// ロードオブジェクトの設定
void GameSceneManager::SetLoadScreen(LoadScreen* loadObject){
	if (m_loadObject)
	{
		m_loadObject->Finalize();
		delete m_loadObject;
	}
	m_loadObject = loadObject;
	m_loadObject->Initialize();
}

//
void GameSceneManager::IsChangeScene(std::string nextSceneName,LoadState useLoadScreen,LoadWaitState useWaitRun){
	m_isChangeScene = true;
	m_nextSceneName = nextSceneName;
	m_useLoadWaitRun = useWaitRun;
	m_useLoadScreen = useLoadScreen;
	m_gameState = eGameState::eNone;
	m_transitionState = eTransitionState::eIn;

}

// ロード
bool GameSceneManager::LoadScene(){
	
	if (!m_isLoadScene) return true;
	
	if (!m_isCreateThread)
	{
		// 初期化処理
		std::thread initializeThred([&](){

			m_isEndInitialize = m_currentScene->Initialize();
			if (!m_isEndInitialize)
			{
				assert(!"Do not Initalize");
			}
		});
		m_isCreateThread = true;
		m_initializeThread = std::move(initializeThred);
	}

	// ロード画面を使うか使わないか
	if (m_useLoadScreen == LoadState::eUse)
	{
		m_loadObject->Run();
	}
	

	// ロードの終了
	if (!m_isEndInitialize){
		return false;
	}
	else{
		m_isLoadScene = false;
	}

	m_initializeThread.join();

	return true;
}

//
bool GameSceneManager::LaodWaitRun(){

	if (m_useLoadWaitRun != LoadWaitState::eUse || m_isLoadWaitEnd) return true;
	
	m_isLoadWaitEnd = m_loadObject->WaitRun();
	
	return m_isLoadWaitEnd;
}

void GameSceneManager::RegisterActorObject(GameActor* actor){
	m_actorManager.AddChild(actor);
}