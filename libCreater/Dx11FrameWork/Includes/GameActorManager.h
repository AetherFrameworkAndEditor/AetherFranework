/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameActor.h
@brief     GameActor管理クラス.とりあえずは衝突判定をサポートする

*******************************************************************************
@date       2016/02/01 24:55
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/02/01 24:55 橋本航
-# Initial Version
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

		void AddChild(GameActor*);
		void Collide();
		void RemoveChild();
	private:
		bool IsHitBoxCollider(GameActor*, GameActor*);
		bool IsHitSphereCollider(GameActor*, GameActor*);
	private:
		std::vector<GameActor*> m_children;
	};
}
#endif