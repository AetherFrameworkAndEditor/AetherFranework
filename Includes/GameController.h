#ifndef _GAMECONTROLLER_H
#define _GAMECONTROLLER_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameController.h
@brief     �R���g���[���[���o�R���ă}�E�X��L�[�{�[�h�փA�N�Z�X����B

*******************************************************************************
@date       2016/2/27
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/

#define DIRECTINPUT_VERSION 0x0800

#include "DirectXEntity.h"
#include "Vector3.h"
#include <Windows.h>
#include <memory>
#include "ViewCamera.h"
#include "GameKeyBord.h"
#include"GameMouse.h"
namespace aetherClass{
	class GameController
	{

	public:
		/*
		@brief          �f�o�C�X�̏�����
		@param          �C���X�^���X�n���h��
		@param          �E�B���h�E�n���h��
		@return         ������ true / ���s�� false
		@exception      none
		*/
		static bool Create(HINSTANCE&, HWND&);
		/*
		@brief          �L�[�{�[�h�I�u�W�F�N�g�̎擾
		@param          none
		@return         �L�[�{�[�h�I�u�W�F�N�g
		@exception      none
		*/
		static GameKeyBord& GetKey();
		/*
		@brief          �}�E�X�I�u�W�F�N�g�̎擾
		@param          none
		@return         �}�E�X�I�u�W�F�N�g
		@exception      none
		*/
		static GameMouse& GetMouse();

		/*
		@brief          �f�o�C�X�̉������
		@param          none
		@return         none
		@exception      none
		*/
		static void Destroy();
		/*
		@brief          �X�V����
		@param          none
		@return         ������ true / ���s�� false
		@exception      none
		*/
		static bool Frame();

	private:
		GameController();
		~GameController();
		/*
		@brief          �f�o�C�X�̏�����
		@param          �C���X�^���X�n���h��
		@param          �E�B���h�E�n���h��
		@return         ������ true / ���s�� false
		@exception      none
		*/
		static bool Initialize(HINSTANCE&, HWND&);

	private:
		static HWND m_hWnd;
	};
}
#endif