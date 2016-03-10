/*
	動作チェック


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

	// デバッグ用コンソールウィンドウの表示
	ConsoleWindow::Create();

	// エントリーポイントの作成
	GameEntry *entry = new GameEntry();

	// 独自クラス
	GameFrame *frame = new GameFrame();
	
	entry->Initialize();
	POINT screen={ 800, 600 };
	// フレームオブジェクトの初期化
	frame->Initialize(*entry->GetWindowHandle(),screen,false,100000);

	// 背景色を好きな色に設定できるよ
	frame->BackgroundColor(Color(0.5, 0.0, 0.0, 0.0));

	// メイン部になるオブジェクトを設定
	entry->SetGameFrame(frame);

	GameScene* scene = new TestScene();
	GameSceneManager::SetCurrentScene(scene);

	auto load = new TestLoadScreen();
	GameSceneManager::SetLoadScreen(load);

	// メインループの開始
	entry->GameRun();

	frame->Finalize();
	delete frame;
	entry->Finalize();
	delete entry;
	

	// デバッグ用コンソールウィンドウの破棄
	ConsoleWindow::Close();
	return 0;
}