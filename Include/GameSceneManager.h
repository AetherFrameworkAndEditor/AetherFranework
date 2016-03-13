/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameSceneManager.h
@brief     シーン管理クラス

*******************************************************************************
@date       2016/01/18 09:36
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/01/18 09:36 橋本航
-# Initial Version


******************************************************************************/
#ifndef _GAMESCENEMANAGER_H
#define _GAMESCENEMANAGER_H
#include <memory>
#include <unordered_map>
#include <thread>
#include <vector>
#include "LoadScreen.h"
#include "GameActorManager.h"
namespace aetherClass{
	class GameScene;

	// ロード画面を使うか使わないか
	enum class LoadState{
		eUse,
		eUnuse,
		eNull
	};

	// ロード画面後のを使うか使わないか
	enum class LoadWaitState{
		eUse,
		eUnuse,
		eNull
	};


	class GameSceneManager
	{
	public:
		GameSceneManager();
		~GameSceneManager();

		/*
		@brief          シーンの初期化処理
		@param[in]      none

		@return         成功時:true/失敗時:fales
		@exception      none
		*/
		bool SceneInitialize();

		/*
		@brief          シーンの更新処理
		@param[in]      none

		@return         成功時:true/失敗時:fales
		                falseを返すとアプリケーションが終了する
		@exception      none
		*/
		bool SceneUpdatar();

		/*
		@brief          シーンの描画処理
		@param[in]      none

		@return         none
		@exception      none
		*/
		void SceneRender();

		/*
		@brief          シーンのUI描画処理
		@param[in]      none

		@return         none
		@exception      none
		*/
		void SceneUIRender();
		
		/*
		@brief          シーンの遷移処理
		@param[in]      

		@return         none
		@exception      none
		*/
		void ChangeScene();

		/*
		@brief          シーンの遷移処理
		@param[in]      変更するシーンの名前
		@param[in]      ロード後の待機処理をするかどうか

		@return         none
		@exception      none
		*/
		void IsChangeScene(std::string, LoadState useLoadScreen, LoadWaitState useWaitProcess);

		/*
		@brief          最初のシーンの設定
		@param[in]      設定するシーンのポインタ

		@return         none
		@exception      none
		*/
		static void SetCurrentScene(GameScene*);

		/*
		@brief          ロード時のオブジェクトを設定
		@param[in]      LoadScreen型オブジェクト

		@return         none
		@exception      none
		*/
		static void SetLoadScreen(LoadScreen*);

		/*
		@brief          シーンの設定
		@param[in]      設定するシーンのポインタ

		@return         none
		@exception      none
		*/
		void RegisterScene(GameScene*);

		/*
		@brief          ActorObjectの登録処理
		@param[in]      GameActor*

		@return         none
		@exception      none
		*/
		void RegisterActorObject(GameActor*);
	private:

		// ゲームの状態管理用
		enum class eGameState{
			eNone,
			eInitialize,
			eUpData,
			eRender,
			eUIRender,
			eFinalize,
			eChange,
		};

		//　トランジション効果の状態管理用
		enum class eTransitionState{
			eNone,
			eIn,
			eOut,
		};
	private:
		
		/*
		@brief          シーンの検索
		@param[in]      検索するシーン名

		@return         none
		@exception      none
		*/
		GameScene* FindScene(std::string);

		/*
		@brief          解放処理
		@param[in]      none

		@return         none
		@exception      none
		*/
		void Finalize();

		/*
		@brief          トランジション効果用
		@param[in]      none

		@return         none
		@exception      none
		*/
		bool SceneTransitionIn();


		/*
		@brief          トランジション効果用
		@param[in]      none

		@return         none
		@exception      none
		*/
		bool SceneTransitionOut();
		
		/*
		@brief          シーンの解放処理
		@param[in]      none

		@return         none
		@exception      none
		*/
		void SceneFinalize();

		/*
		@brief          使うシーンの入れ替え
		@param[in]      none

		@return         none
		@exception      none
		*/
		void ChangeCurrentScene();

		/*
		@brief          ロードの処理
		@param[in]      none

		@return         none
		@exception      none
		*/
		bool LoadScene();

		/*
		@brief          ロードの待機処理
		@param[in]      none

		@return         none
		@exception      none
		*/
		bool LaodWaitRun();
		

	private:
		static std::unordered_map<std::string, GameScene*> m_scenesMap; // シーンを登録するコンテナ
		static GameScene* m_currentScene;    // 現在のシーン
		static LoadScreen* m_loadObject;       // ロード時に使うオブジェクト
		static eGameState m_gameState;      // 現在のゲームの状態
		static eTransitionState m_transitionState;   // トランジション効果の状態
		static std::string m_nextSceneName;          // 次のシーンの名前を保存用
		static std::string m_currentSceneName;       // 現在のシーンの名前
		static bool m_isChangeScene;           // シーンを切り替えるかのフラグ
		static bool m_isLoadScene;             // ロード処理を行うかのフラグ
		static GameActorManager m_actorManager; // アクター管理オブジェクト
		static LoadWaitState m_useLoadWaitRun;    // ロード後に何らかの処理ができる
		static LoadState m_useLoadScreen;

		bool m_isTransitionInEnd;               // トランジション(in)の終わったかのフラグ
		bool m_isTransitionOutEnd;               // トランジション(out)の終わったかのフラグ
		bool m_isLoadWaitEnd;                 // ロードの待ちの処理が終わったかのフラグ
		bool m_isCreateThread;                // スレッドを作成したかのフラグ
		bool m_isEndInitialize;               // 初期化処理が終わったかのフラグ
		std::thread m_initializeThread;       // 初期化処理を行うスレッドオブジェクト
		int m_loadWaitTime;
	
	};

}

#endif