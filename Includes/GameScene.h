/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameScene.h
@brief     シーンを作成するとき継承して作成する

*******************************************************************************
@date       2016/01/18
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/
#ifndef _GAMESCENE_H
#define _GAMESCENE_H
#include <string>
#include "GameSceneManager.h"

#define TRANSITION_END true   // トランジション効果を終了させたいならこれを返す
#define TRANSITION_ING false  // トランジション効果を継続の場合はこれを返す
namespace{
	const bool kTransitionEnd = true;       // トランジション効果を終了させたいならこれを返す
	const bool kTransitionning = false;     // トランジション効果を継続の場合はこれを返す
}
namespace aetherClass{
	class GameScene
	{
	public:

		/*
		@brief          シーン情報の登録
		@param[in]      name     GameSceneの名前を設定
		@param[in]      manager  GameSceneManagerオブジェクト

		@return         none
		@exception      none
		*/
		GameScene(const std::string &name,GameSceneManager& manager):
			m_sceneManager(manager),
			m_sceneName(name){}

		virtual~GameScene() = default;

		/*
		@brief          シーンの初期化処理
		@param[in]      none
		@return         成功時: true/失敗時: false
		@exception      none
		*/
		virtual bool Initialize() = 0;

		/*
		@brief          シーンの更新処理
		@param[in]      none

		@return         none
		@exception      none
		*/
		virtual bool Updater() = 0;

		/*
		@brief          シーンの描画処理
		@param[in]      none

		@return         none
		@exception      none
		*/
		virtual void Render() = 0;

		/*
		@brief          UIの描画処理
		@param[in]      none

		@return         none
		@exception      none
		*/
		virtual void UIRender(){ return; }


		/*
		@brief          シーンの解放処理
		@param[in]      none

		@return         none
		@exception      none
		*/
		virtual void Finalize() = 0;

		/*
		@brief          トランジション効果の処理をを設定する
		@param[in]      none

		@return         true
		@exception      none
		*/
		virtual bool TransitionIn(){ return true; }

		/*
		@brief          トランジション効果の処理をを設定する
		@param[in]      none

		@return         トランジション効果の終了true
		@exception      none
		*/
		virtual bool TransitionOut(){ return true; }

		/*
		@brief          シーンの名前を取得
		@param[in]      none

		@return         コンストラクタで登録したシーンの名前
		@exception      none
		*/
		virtual std::string GetName()final{ return m_sceneName; }

		/*
		@brief          GameSceneManagerオブジェクト取得用
		@param[in]      none

		@return         GameSceneManager型オブジェクト
		@exception      none
		*/
		virtual GameSceneManager& GetManager(){ return m_sceneManager; }
	protected:

		/*
		@brief          シーンの遷移時に使用
		@param[in]      登録されているシーン名
		@param[in]      登録されているロードオブジェクトのWaitRun関数を使うか使わないか
		@return         none
		@exception      none
		*/
		virtual void ChangeScene(const std::string& afterSceneName,LoadState useLoad,LoadWaitState useLoadWaitRun)final{
			 m_sceneManager.IsChangeScene(afterSceneName,useLoad,useLoadWaitRun);
		}

		/*
		@brief          シーンの登録
		@param[in]      登録するシーンのポインタ

		@return         true
		@exception      none
		*/
		virtual void RegisterScene(GameScene* addScene)final{
			m_sceneManager.RegisterScene(addScene);
		}

		/*
		@brief          アクターの登録
		@param[in]      登録するアクターのポインタ

		@return         true
		@exception      none
		*/
		virtual void RegisterActor(GameActor* addActor)final{
			m_sceneManager.RegisterActorObject(addActor);
		}
	private:
		GameSceneManager& m_sceneManager;
		const std::string m_sceneName;
		
	};
}

#endif