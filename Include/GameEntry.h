/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameEntry.h
@brief     �G���g���[�|�C���g�쐬�p�N���X

*******************************************************************************
@date       2016/01/06 23:06
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/01/06 23:06 ���{�q
-# Initial Version
- 2016/01/12 10:07 ���{�q
-# remove IsEnd function
******************************************************************************/
#ifndef _GAMEENTRY_H
#define _GAMEENTRY_H
#include "ConsoleWindow.h"
#include "GameFrame.h"
#include <memory>
#include <string>
#include <Windows.h>
namespace aetherClass{

	namespace{
		const LPCWSTR kWindowName = L"AetherFrameWork";
		const int kWindowWidth = 800;
		const int kWindowHeight = 600;
	}

	class GameEntry
	{
	public:
		GameEntry();
		~GameEntry();
	
		/*
		@brief          �������p
		@param[in]      �t���X�N���[�� true/�E�B���h�E���[�h false    default[false]
		@param[in]      �E�B���h�E�̖��O    default[kWindowName]
		@param[in]      �E�B���h�E�̕�    default[kWindowWidth]
		@param[in]      �E�B���h�E�̍���    default[kWindowHeight]
		@return         �������Ftrue/���s��: false
		@exception      none
		*/
		virtual bool Initialize(
			const bool isFullScreen = false,
			LPCWSTR windowName = kWindowName, 
			const int width = kWindowWidth,
			const int height = kWindowHeight)final;
		
		/*
		@brief          ����p
		@param[in]      none
		@return         none
		@exception      none
		*/
		virtual void Finalize()final;


		/*
		@brief          ���C�����[�v�BSetFrameObject�Őݒ肳�ꂽGameFrame�N���X��Frame�֐������s�����
		@param          none
		@return         �������Ftrue/���s��: false
		@exception      none
		*/
		virtual void GameRun()final;

		/*
		@brief          ���b�Z�[�W�n���h���[�B�L�[�̎󂯎��
		@param[in]      �E�B���h�E�n���h��
		@param[in]      ���b�Z�[�W
		@param[in]      wParam
		@param[in]      lParam
		@return         �������Ftrue/���s��: false
		@exception      none
		*/
		virtual LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM)final;

		/*
		@brief          GameFrame�^���p�������Ǝ��N���X��ۑ��B
		                �����œn���ꂽGameFrame�^�I�u�W�F�N�g��FrameRunningBuffer�֐������ۂ̃��C�����ɂȂ�
		@param[in]      �Ǝ��Ɏ�������GameFrame���p�������N���X��n��
		@return         none
		@exception      none
		*/
		virtual void SetGameFrame(GameFrame*)final;

		/*
		@brief          �E�B���h�E�̃n���h�����擾�p
		@param          none
		@return         HWND�^�I�u�W�F�N�g
		@exception      none
		*/
		const HWND* GetWindowHandle();

	private:

		/*
		@brief          �E�B���h�E�̏������p
		@param[in]      �t���X�N���[���F true/�E�B���h�E���[�h�F false
		@return         POINT�^�ɃX�N���[���̕��ƍ������擾�����ϐ�
		@exception      none
		*/
		virtual POINT InitalizeWindow(const bool isFull, LPCWSTR windowName)final;

		/*
		@brief          �������p.�I�[�o�[���C�h���邱�ƂœƎ������������ł��� 
		@param[in]      none
		@return         �������Ftrue/���s��: false
		@exception      none
		*/
		virtual bool InitializeBuffer(){ return true; };

		/*
		@brief          ����p.�I�[�o�[���C�h���邱�ƂœƎ������������ł���
		@param[in]      none
		@return         �������Ftrue/���s��: false
		@exception      none
		*/
		virtual void FinalizationBuffer(){ return; };

	private:
		// GameFrame�I�u�W�F�N�g�̃A�h���X�ۑ��p
		static GameFrame* m_frame;

		unsigned int m_windowWidth;
		unsigned int m_windowHeight;

		
		LPCWSTR m_windowName;
		HINSTANCE m_hInstance;
		HWND m_hWnd;
	};

	
}

#endif