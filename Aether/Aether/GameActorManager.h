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

		/*
		@brief          �q�I�u�W�F�N�g�Ƃ��ēo�^
		@param[in]      GameActor�N���X�̃|�C���^

		@return         none
		@exception      none
		*/
		void AddChild(GameActor*);

		/*
		@brief          �Փˏ�񌟍��p
		@param          none

		@return         none
		@exception      none
		*/
		void Collide();

		/*
		@brief          �o�^�����q�I�u�W�F�N�g�����ׂĉ��
		@param          none

		@return         none
		@exception      none
		*/
		void RemoveChild();
	private:

		/*
		@brief          �o�^�����q�I�u�W�F�N�g��Box�R���C�_�[�������������𒲂ׂ�
		@param          none

		@return         �Փˎ��Ftrue
		@exception      none
		*/
		bool IsHitBoxCollider(GameActor*, GameActor*);

		/*
		@brief          �o�^�����q�I�u�W�F�N�g��Sphere�R���C�_�[�������������𒲂ׂ�
		@param          none

		@return         �Փˎ��Ftrue
		@exception      none
		*/
		bool IsHitSphereCollider(GameActor*, GameActor*);
	private:
		std::vector<GameActor*> m_children;
	};
}
#endif