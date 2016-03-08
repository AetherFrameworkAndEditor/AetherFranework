/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameSceneManager.h
@brief     �V�[���Ǘ��N���X

*******************************************************************************
@date       2016/01/18 09:36
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/01/18 09:36 ���{�q
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

	// ���[�h��ʂ��g�����g��Ȃ���
	enum class LoadState{
		eUse,
		eUnuse,
		eNull
	};

	// ���[�h��ʌ�̂��g�����g��Ȃ���
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
		@brief          �V�[���̏���������
		@param[in]      none

		@return         ������:true/���s��:fales
		@exception      none
		*/
		bool SceneInitialize();

		/*
		@brief          �V�[���̍X�V����
		@param[in]      none

		@return         ������:true/���s��:fales
		                false��Ԃ��ƃA�v���P�[�V�������I������
		@exception      none
		*/
		bool SceneUpdatar();

		/*
		@brief          �V�[���̕`�揈��
		@param[in]      none

		@return         none
		@exception      none
		*/
		void SceneRender();

		/*
		@brief          �V�[����UI�`�揈��
		@param[in]      none

		@return         none
		@exception      none
		*/
		void SceneUIRender();
		
		/*
		@brief          �V�[���̑J�ڏ���
		@param[in]      

		@return         none
		@exception      none
		*/
		void ChangeScene();

		/*
		@brief          �V�[���̑J�ڏ���
		@param[in]      �ύX����V�[���̖��O
		@param[in]      ���[�h��̑ҋ@���������邩�ǂ���

		@return         none
		@exception      none
		*/
		void IsChangeScene(std::string, LoadState useLoadScreen, LoadWaitState useWaitProcess);

		/*
		@brief          �ŏ��̃V�[���̐ݒ�
		@param[in]      �ݒ肷��V�[���̃|�C���^

		@return         none
		@exception      none
		*/
		static void SetCurrentScene(GameScene*);

		/*
		@brief          ���[�h���̃I�u�W�F�N�g��ݒ�
		@param[in]      LoadScreen�^�I�u�W�F�N�g

		@return         none
		@exception      none
		*/
		static void SetLoadScreen(LoadScreen*);

		/*
		@brief          �V�[���̐ݒ�
		@param[in]      �ݒ肷��V�[���̃|�C���^

		@return         none
		@exception      none
		*/
		void RegisterScene(GameScene*);

		/*
		@brief          ActorObject�̓o�^����
		@param[in]      GameActor*

		@return         none
		@exception      none
		*/
		void RegisterActorObject(GameActor*);
	private:

		// �Q�[���̏�ԊǗ��p
		enum class eGameState{
			eNone,
			eInitialize,
			eUpData,
			eRender,
			eUIRender,
			eFinalize,
			eChange,
		};

		//�@�g�����W�V�������ʂ̏�ԊǗ��p
		enum class eTransitionState{
			eNone,
			eIn,
			eOut,
		};
	private:
		
		/*
		@brief          �V�[���̌���
		@param[in]      ��������V�[����

		@return         none
		@exception      none
		*/
		GameScene* FindScene(std::string);

		/*
		@brief          �������
		@param[in]      none

		@return         none
		@exception      none
		*/
		void Finalize();

		/*
		@brief          �g�����W�V�������ʗp
		@param[in]      none

		@return         none
		@exception      none
		*/
		bool SceneTransitionIn();


		/*
		@brief          �g�����W�V�������ʗp
		@param[in]      none

		@return         none
		@exception      none
		*/
		bool SceneTransitionOut();
		
		/*
		@brief          �V�[���̉������
		@param[in]      none

		@return         none
		@exception      none
		*/
		void SceneFinalize();

		/*
		@brief          �g���V�[���̓���ւ�
		@param[in]      none

		@return         none
		@exception      none
		*/
		void ChangeCurrentScene();

		/*
		@brief          ���[�h�̏���
		@param[in]      none

		@return         none
		@exception      none
		*/
		bool LoadScene();

		/*
		@brief          ���[�h�̑ҋ@����
		@param[in]      none

		@return         none
		@exception      none
		*/
		bool LaodWaitRun();
		

	private:
		static std::unordered_map<std::string, GameScene*> m_scenesMap; // �V�[����o�^����R���e�i
		static GameScene* m_currentScene;    // ���݂̃V�[��
		static LoadScreen* m_loadObject;       // ���[�h���Ɏg���I�u�W�F�N�g
		static eGameState m_gameState;      // ���݂̃Q�[���̏��
		static eTransitionState m_transitionState;   // �g�����W�V�������ʂ̏��
		static std::string m_nextSceneName;          // ���̃V�[���̖��O��ۑ��p
		static std::string m_currentSceneName;       // ���݂̃V�[���̖��O
		static bool m_isChangeScene;           // �V�[����؂�ւ��邩�̃t���O
		static bool m_isLoadScene;             // ���[�h�������s�����̃t���O
		static GameActorManager m_actorManager; // �A�N�^�[�Ǘ��I�u�W�F�N�g
		static LoadWaitState m_useLoadWaitRun;    // ���[�h��ɉ��炩�̏������ł���
		static LoadState m_useLoadScreen;

		bool m_isTransitionInEnd;               // �g�����W�V����(in)�̏I��������̃t���O
		bool m_isTransitionOutEnd;               // �g�����W�V����(out)�̏I��������̃t���O
		bool m_isLoadWaitEnd;                 // ���[�h�̑҂��̏������I��������̃t���O
		bool m_isCreateThread;                // �X���b�h���쐬�������̃t���O
		bool m_isEndInitialize;               // �������������I��������̃t���O
		std::thread m_initializeThread;       // �������������s���X���b�h�I�u�W�F�N�g
		int m_loadWaitTime;
	
	};

}

#endif