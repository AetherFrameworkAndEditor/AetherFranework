/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameActor.h
@brief     GameActor�Ǘ��N���X.�Ƃ肠�����͏Փ˔�����T�|�[�g����

*******************************************************************************
@date       2016/02/01 24:55
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/02/01 24:55 ���{�q
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