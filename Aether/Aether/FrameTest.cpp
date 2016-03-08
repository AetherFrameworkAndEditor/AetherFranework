#include "ConsoleWindow.h"
#include"GameFrame.h"
#include"WindowBase.h"
#include "TestScene.h"
#include"AetherWindow.h"
#include<Windows.h>

using namespace aetherClass;
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow){

	// デバッグ用コンソールウィンドウの表示
	ConsoleWindow::Create();

	// 独自クラス
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
	// フレームオブジェクトの初期化
	frame->Initialize(window,3,1000,1);

	// 背景色を好きな色に設定できるよ
	frame->BackgroundColor(Color(0.5, 0.0, 0.0, 0.0));

	GameScene* scene = new TestScene();
	GameSceneManager::SetCurrentScene(scene);

	// メインループの開始
	frame->GameRun();

	frame->Finalize();
	delete frame;
	delete[] window;

	// デバッグ用コンソールウィンドウの破棄
	ConsoleWindow::Close();
	return 0;
}