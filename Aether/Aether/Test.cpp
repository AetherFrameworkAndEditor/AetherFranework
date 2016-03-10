/*
	����`�F�b�N


*/
#include <chrono>
#include <iostream>
#include "Direct3DManager.h"
#include "ConsoleWindow.h"
#include"GameEntry.h"
#include"GameFrame.h"
#include "GameSceneManager.h"
#include "GameScene.h"
#include "TestScene.h"
#include "TestScene2.h"
#include "TestLoadScreen.h"
using namespace aetherClass;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow){

	// �f�o�b�O�p�R���\�[���E�B���h�E�̕\��
	ConsoleWindow::Create();

	// �G���g���[�|�C���g�̍쐬
	GameEntry *entry = new GameEntry();

	// �Ǝ��N���X
	GameFrame *frame = new GameFrame();
	
	entry->Initialize();
	POINT screen={ 800, 600 };
	// �t���[���I�u�W�F�N�g�̏�����
	frame->Initialize(*entry->GetWindowHandle(),screen,false,100000);

	// �w�i�F���D���ȐF�ɐݒ�ł����
	frame->BackgroundColor(Color(0.5, 0.0, 0.0, 0.0));

	// ���C�����ɂȂ�I�u�W�F�N�g��ݒ�
	entry->SetGameFrame(frame);

	GameScene* scene = new TestScene();
	GameSceneManager::SetCurrentScene(scene);

	auto load = new TestLoadScreen();
	GameSceneManager::SetLoadScreen(load);

	// ���C�����[�v�̊J�n
	entry->GameRun();

	frame->Finalize();
	delete frame;
	entry->Finalize();
	delete entry;
	

	// �f�o�b�O�p�R���\�[���E�B���h�E�̔j��
	ConsoleWindow::Close();
	return 0;
}