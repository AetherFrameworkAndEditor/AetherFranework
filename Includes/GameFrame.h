/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameFrame.h
@brief     ゲームの１フレームごとの処理を行う

*******************************************************************************
@date       2016/01/06
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _GAMEFRAME_H
#define _GAMEFRAME_H
#include "Direct3DManager.h"
#include "GameSceneManager.h"
#include"GameController.h"
#include"DirectXEntity.h"
#include "GameScene.h"
#include <memory>
namespace aetherClass{

	namespace{
		const bool kVsyncEnabled = true;
		const float kScreenDepth = 1000.0f;
		const float kScreenNear = 1.0f;
	}

	
	class GameFrame
	{

	public:
		GameFrame();
		virtual ~GameFrame() = default;

		/*
		@brief          初期化用
		@param[in]      ウィンドウハンドルリスト
		@param[in]      ウィンドウの数
		@param[in]      スクリーンの奥行の広さ 0.1以上の値    default[1000.0f]
		@param[in]      スクリーンの近さ 0.0~1.0の間の値    default[1.0f]
		@return         成功時：true/失敗時: false
		@exception      none
		*/
		virtual bool Initialize(WindowBase **window, UINT numWindow,const float screenDepth = kScreenDepth, const float screenNear = kScreenNear)final;

		/*
		@brief          解放用
		@param          none
		@return         none
		@exception      none
		*/
		virtual void Finalize()final;

		/*
		@brief          フレームごとに更新される関数
		@param          none
		@return         成功時：true/失敗時: false
		@exception      none
		*/
		virtual bool FrameRunning()final;

		/*
		@brief          画面全体を塗りつぶす色の設定
		@param[in]      Color型のオブジェクト
		@return         成功時：true/失敗時: false
		@exception      none
		*/
		virtual void BackgroundColor(Color)final;

		/*
		@brief          メインループの開始
		@param          none
		@return         none
		@exception      none
		*/
		virtual void GameRun()final;

	private:

		/*
		@brief          初期化用.オーバーライドすることで独自処理を実装できる
		@param          none
		@return         none
		@exception      none
		*/
		virtual bool InitializeBuffer(){ return true; }

		/*
		@brief          1フレームごとに更新される。.オーバーライドすることで独自処理を実装できる
		@param          none
		@return         none
		@exception      none
		*/
		virtual bool FrameRunningBuffer(){ return true; }

		/*
		@brief          解放用。.オーバーライドすることで独自処理を実装できる
		@param          none
		@return         none
		@exception      none
		*/
		virtual void FinalizeBuffer(){ return; }

	private:
		static Color m_backgroundColor;
		std::unique_ptr<Direct3DManager> m_direct3D;
		std::unique_ptr<GameSceneManager> m_sceneManager;
		std::unique_ptr<GameScene> m_scene;
		DirectXEntity m_entity;

	};

}

#endif