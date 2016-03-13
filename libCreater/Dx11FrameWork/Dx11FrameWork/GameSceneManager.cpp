#include "GameSceneManager.h"
#include "GameScene.h"
#include "NullLoadScreen.h"
#include "NullScene.h"
#include <assert.h>
#include <iostream>
using namespace aetherClass;

std::unordered_map<std::string, GameScene*> GameSceneManager::m_scenesMap;

/*	Null�I�u�W�F�N�g�ŏ�����*/
GameScene* GameSceneManager::m_currentScene = new NullScene();
LoadScreen* GameSceneManager::m_loadObject = new NullLoadScreen();

/*	�X�e�[�g�̏�����	*/
GameSceneManager::eGameState GameSceneManager::m_gameState = GameSceneManager::eGameState::eNone;
GameSceneManager::eTransitionState GameSceneManager::m_transitionState = GameSceneManager::eTransitionState::eNone;

/*	���ꂼ��̖��O�̏�����	*/
std::string GameSceneManager::m_nextSceneName = "None";
std::string GameSceneManager::m_currentSceneName = "None";

/*	�t���O�֘A	*/
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

// �o�^����
void GameSceneManager::RegisterScene(GameScene* registerScene){
	// �o�^�ς݂Ȃ牽�����Ȃ�
	if (FindScene(registerScene->GetName())) return;

	m_scenesMap.insert(std::make_pair(registerScene->GetName(), registerScene));
}

// �����p
GameScene* GameSceneManager::FindScene(std::string name){
	auto findMap = m_scenesMap.find(name);
	if (findMap == m_scenesMap.end()) return nullptr;
	
	return findMap->second;
}

// �V�[���̏���������
bool GameSceneManager::SceneInitialize(){
	if (m_gameState != eGameState::eInitialize) return true;
	
	m_currentScene->Initialize();

	m_gameState = eGameState::eRender;

	return true;
}

// �V�[���̕`�揈��
void GameSceneManager::SceneRender(){
	if (m_gameState != eGameState::eRender)return;
	
	m_currentScene->Render();

	m_gameState = eGameState::eUIRender;
	return;
}

// �V�[���̕`�揈��
void GameSceneManager::SceneUIRender(){
	if (m_gameState != eGameState::eUIRender) return;
	
	m_currentScene->UIRender();

	m_gameState = eGameState::eUpData;
	return;
}

// �V�[���̍X�V����
bool GameSceneManager::SceneUpdatar(){
	if (m_gameState != eGameState::eUpData) return true;
	
	bool result;
	result = m_currentScene->Updater();

	// �S�I�u�W�F�N�g�̏Փ˔��茟��
	m_actorManager.Collide();

	m_gameState = eGameState::eRender;
	return result;
}

// �V�[���̉������
void GameSceneManager::SceneFinalize(){
	if (m_gameState != eGameState::eFinalize) return;
	
	m_currentScene->Finalize();
	m_actorManager.RemoveChild();
	m_gameState = eGameState::eChange;
	return;
}


// �������
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

	/*	�X�e�[�g�̏�����	*/
	m_gameState = GameSceneManager::eGameState::eNone;
	m_transitionState = GameSceneManager::eTransitionState::eNone;

	/*	���ꂼ��̖��O�̏�����	*/
	m_nextSceneName = "None";

	// �t���O�̏�����
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

	// ���݂��Ă�����z�񂩂�폜
	if (prevScene != m_scenesMap.end())
	{
		m_scenesMap.erase(prevScene);
	}
	m_currentScene = FindScene(m_nextSceneName);

	// ����ɓ����Ă邩�`�F�b�N
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


// �J�����g�����Ɉړ�����V�[���ɕς���
void GameSceneManager::ChangeScene(){
	
	if (!m_isChangeScene) return;

	// �g�����W�V�����n�܂�
	m_isTransitionInEnd = SceneTransitionIn();
	
	// �܂��I����ĂȂ�
	if (!m_isTransitionInEnd) return;
	
	// �������
	SceneFinalize();

	// �g���V�[���̓���ւ�
	ChangeCurrentScene();

	// TODO: ���[�h�Ə����������
	if (!LoadScene())
	{
		return;
	}

	// ���[�h�̑ҋ@����
	if (!LaodWaitRun())
	{
		return;
	}

	// �g�����W�V�����̌Ăяo��
	m_isTransitionOutEnd = SceneTransitionOut();

	if (!m_isTransitionOutEnd) return;
	
	return;
}

// �g�����W�V��������IN
bool GameSceneManager::SceneTransitionIn(){
	if (m_transitionState != eTransitionState::eIn) return true;
	
	bool result = false;
	
	result = m_currentScene->TransitionIn();

	// in���������Ȃ���`�悷�邽��
	SceneRender();

	if (!result) return false;
	
	// �X�e�[�g�̕ύX
	m_gameState = eGameState::eFinalize;
	m_transitionState = eTransitionState::eOut;
	m_isLoadWaitEnd = false;
	return true;
}

// �g�����W�V��������OUT
bool GameSceneManager::SceneTransitionOut(){
	if (m_transitionState != eTransitionState::eOut) return true;
	
	bool result = false;
	m_gameState = eGameState::eRender;
	result = m_currentScene->TransitionOut();
	// out���������Ȃ���`�悷�邽��
	SceneRender();

	if (!result) return false;
	
	m_gameState = eGameState::eRender;
	m_transitionState = eTransitionState::eNone;
	m_isChangeScene = false;
	return true;
}

// �J�����g�V�[���̓o�^
void GameSceneManager::SetCurrentScene(GameScene* scene){
	m_currentScene = scene;
	m_gameState = eGameState::eInitialize;
	m_currentSceneName = m_currentScene->GetName();
}

// ���[�h�I�u�W�F�N�g�̐ݒ�
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

// ���[�h
bool GameSceneManager::LoadScene(){
	
	if (!m_isLoadScene) return true;
	
	if (!m_isCreateThread)
	{
		// ����������
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

	// ���[�h��ʂ��g�����g��Ȃ���
	if (m_useLoadScreen == LoadState::eUse)
	{
		m_loadObject->Run();
	}
	

	// ���[�h�̏I��
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