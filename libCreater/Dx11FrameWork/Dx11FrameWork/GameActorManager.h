/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameActor.h
@brief     GameActor管理クラス.各シーンで登録することで描画処理やアップデート処理を呼ぶようにする

*******************************************************************************
@date       2016/02/01
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/
#ifndef _GAMEACTORMANAGER_H
#define _GAMEACTORMANAGER_H
#include "GameActor.h"
namespace aetherClass{

	class GameActorManager
	{
	public:
		GameActorManager();
		~GameActorManager();

		/*
		@brief          子オブジェクトとして登録
		@param[in]      GameActorクラスのポインタ

		@return         none
		@exception      none
		*/
		void AddChild(GameActor*);

		/*
		@brief          衝突情報検索用
		@param          none

		@return         none
		@exception      none
		*/
		void Collide();

		/*
		@brief          登録した子オブジェクトをすべて解放
		@param          none

		@return         none
		@exception      none
		*/
		void RemoveChild();
	private:

		/*
		@brief          登録した子オブジェクトのBoxコライダーが当たったかを調べる
		@param          none

		@return         衝突時：true
		@exception      none
		*/
		bool IsHitBoxCollider(GameActor*, GameActor*);

		/*
		@brief          登録した子オブジェクトのSphereコライダーが当たったかを調べる
		@param          none

		@return         衝突時：true
		@exception      none
		*/
		bool IsHitSphereCollider(GameActor*, GameActor*);
	private:
		std::vector<GameActor*> m_children;
	};
}
#endif