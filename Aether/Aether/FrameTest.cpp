#include "ConsoleWindow.h"
#include"GameFrame.h"
#include"WindowBase.h"
#include "TestScene.h"
#include"AetherWindow.h"
#include<Windows.h>

using namespace aetherClass;
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow){

	// �f�o�b�O�p�R���\�[���E�B���h�E�̕\��
	ConsoleWindow::Create();

	// �Ǝ��N���X
	GameFrame *frame = new GameFrame();


	Vector2 screenSize(800, 600);
	WindowBase *window[3];
	window[0] = new AetherWindow();
	window[1] = new AetherWindow();
	window[2] = new WindowBase();

	aetherClass::WindowBase::WindowStyleDesc desc;
	desc._windowStyle = WS_OVERLAPPEDWINDOW;

	window[0]->SetWindowStyles(desc);

	window[0]->Create(L"First", screenSize, Vector2(100, 100));
	window[1]->Create(L"Second", screenSize);
	window[2]->Create(L"popUp", Vector2(100, 100));
	// �t���[���I�u�W�F�N�g�̏�����
	frame->Initialize(window,3,1000,1);

	// �w�i�F���D���ȐF�ɐݒ�ł����
	frame->BackgroundColor(Color(0.5, 0.0, 0.0, 0.0));

	GameScene* scene = new TestScene();
	GameSceneManager::SetCurrentScene(scene);

	// ���C�����[�v�̊J�n
	frame->GameRun();

	frame->Finalize();
	delete frame;
	delete[] window;

	// �f�o�b�O�p�R���\�[���E�B���h�E�̔j��
	ConsoleWindow::Close();
	return 0;
}