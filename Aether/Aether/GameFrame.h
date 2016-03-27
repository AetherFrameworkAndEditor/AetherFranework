/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameFrame.h
@brief     �Q�[���̂P�t���[�����Ƃ̏������s��

*******************************************************************************
@date       2016/01/06
@author     ���{�q
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
		@brief          �������p
		@param[in]      �E�B���h�E�n���h�����X�g
		@param[in]      �E�B���h�E�̐�
		@param[in]      �X�N���[���̉��s�̍L�� 0.1�ȏ�̒l    default[1000.0f]
		@param[in]      �X�N���[���̋߂� 0.0~1.0�̊Ԃ̒l    default[1.0f]
		@return         �������Ftrue/���s��: false
		@exception      none
		*/
		virtual bool Initialize(WindowBase **window, UINT numWindow,const float screenDepth = kScreenDepth, const float screenNear = kScreenNear)final;

		/*
		@brief          ����p
		@param          none
		@return         none
		@exception      none
		*/
		virtual void Finalize()final;

		/*
		@brief          �t���[�����ƂɍX�V�����֐�
		@param          none
		@return         �������Ftrue/���s��: false
		@exception      none
		*/
		virtual bool FrameRunning()final;

		/*
		@brief          ��ʑS�̂�h��Ԃ��F�̐ݒ�
		@param[in]      Color�^�̃I�u�W�F�N�g
		@return         �������Ftrue/���s��: false
		@exception      none
		*/
		virtual void BackgroundColor(Color)final;

		/*
		@brief          ���C�����[�v�̊J�n
		@param          none
		@return         none
		@exception      none
		*/
		virtual void GameRun()final;

	private:

		/*
		@brief          �������p.�I�[�o�[���C�h���邱�ƂœƎ������������ł���
		@param          none
		@return         none
		@exception      none
		*/
		virtual bool InitializeBuffer(){ return true; }

		/*
		@brief          1�t���[�����ƂɍX�V�����B.�I�[�o�[���C�h���邱�ƂœƎ������������ł���
		@param          none
		@return         none
		@exception      none
		*/
		virtual bool FrameRunningBuffer(){ return true; }

		/*
		@brief          ����p�B.�I�[�o�[���C�h���邱�ƂœƎ������������ł���
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