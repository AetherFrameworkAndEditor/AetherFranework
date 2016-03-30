/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameScene.h
@brief     �V�[�����쐬����Ƃ��p�����č쐬����

*******************************************************************************
@date       2016/01/18
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/
#ifndef _GAMESCENE_H
#define _GAMESCENE_H
#include <string>
#include "GameSceneManager.h"

#define TRANSITION_END true   // �g�����W�V�������ʂ��I�����������Ȃ炱���Ԃ�
#define TRANSITION_ING false  // �g�����W�V�������ʂ��p���̏ꍇ�͂����Ԃ�
namespace{
	const bool kTransitionEnd = true;       // �g�����W�V�������ʂ��I�����������Ȃ炱���Ԃ�
	const bool kTransitionning = false;     // �g�����W�V�������ʂ��p���̏ꍇ�͂����Ԃ�
}
namespace aetherClass{
	class GameScene
	{
	public:

		/*
		@brief          �V�[�����̓o�^
		@param[in]      name     GameScene�̖��O��ݒ�
		@param[in]      manager  GameSceneManager�I�u�W�F�N�g

		@return         none
		@exception      none
		*/
		GameScene(const std::string &name,GameSceneManager& manager):
			m_sceneManager(manager),
			m_sceneName(name){}

		virtual~GameScene() = default;

		/*
		@brief          �V�[���̏���������
		@param[in]      none
		@return         ������: true/���s��: false
		@exception      none
		*/
		virtual bool Initialize() = 0;

		/*
		@brief          �V�[���̍X�V����
		@param[in]      none

		@return         none
		@exception      none
		*/
		virtual bool Updater() = 0;

		/*
		@brief          �V�[���̕`�揈��
		@param[in]      none

		@return         none
		@exception      none
		*/
		virtual void Render() = 0;

		/*
		@brief          UI�̕`�揈��
		@param[in]      none

		@return         none
		@exception      none
		*/
		virtual void UIRender(){ return; }


		/*
		@brief          �V�[���̉������
		@param[in]      none

		@return         none
		@exception      none
		*/
		virtual void Finalize() = 0;

		/*
		@brief          �g�����W�V�������ʂ̏�������ݒ肷��
		@param[in]      none

		@return         true
		@exception      none
		*/
		virtual bool TransitionIn(){ return true; }

		/*
		@brief          �g�����W�V�������ʂ̏�������ݒ肷��
		@param[in]      none

		@return         �g�����W�V�������ʂ̏I��true
		@exception      none
		*/
		virtual bool TransitionOut(){ return true; }

		/*
		@brief          �V�[���̖��O���擾
		@param[in]      none

		@return         �R���X�g���N�^�œo�^�����V�[���̖��O
		@exception      none
		*/
		virtual std::string GetName()final{ return m_sceneName; }

		/*
		@brief          GameSceneManager�I�u�W�F�N�g�擾�p
		@param[in]      none

		@return         GameSceneManager�^�I�u�W�F�N�g
		@exception      none
		*/
		virtual GameSceneManager& GetManager(){ return m_sceneManager; }
	protected:

		/*
		@brief          �V�[���̑J�ڎ��Ɏg�p
		@param[in]      �o�^����Ă���V�[����
		@param[in]      �o�^����Ă��郍�[�h�I�u�W�F�N�g��WaitRun�֐����g�����g��Ȃ���
		@return         none
		@exception      none
		*/
		virtual void ChangeScene(const std::string& afterSceneName,LoadState useLoad,LoadWaitState useLoadWaitRun)final{
			 m_sceneManager.IsChangeScene(afterSceneName,useLoad,useLoadWaitRun);
		}

		/*
		@brief          �V�[���̓o�^
		@param[in]      �o�^����V�[���̃|�C���^

		@return         true
		@exception      none
		*/
		virtual void RegisterScene(GameScene* addScene)final{
			m_sceneManager.RegisterScene(addScene);
		}

		/*
		@brief          �A�N�^�[�̓o�^
		@param[in]      �o�^����A�N�^�[�̃|�C���^

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