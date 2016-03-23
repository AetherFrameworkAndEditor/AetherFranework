/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameActor.h
@brief     GameActor�Ǘ��N���X.�e�V�[���œo�^���邱�Ƃŕ`�揈����A�b�v�f�[�g�������ĂԂ悤�ɂ���

*******************************************************************************
@date       2016/02/01
@author     ���{�q
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