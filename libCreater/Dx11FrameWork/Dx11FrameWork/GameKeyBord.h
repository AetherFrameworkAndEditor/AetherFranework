/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameKeyBord.h
@brief     �L�[���͊Ǘ��N���X

*******************************************************************************
@date       2016/2/27
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/
#ifndef _GAMEKEYBORD_H
#define _GAMEKEYBORD_H
#include<dinput.h>

#ifndef _CONTROLLER_
#define _CONTROLLER_
#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#endif

namespace aetherClass{
	class GameKeyBord
	{
	public:
		GameKeyBord();
		~GameKeyBord();

		/*
		@brief          �f�o�C�X�̏�����
		@param          �C���X�^���X�n���h��
		@param          �E�B���h�E�n���h��
		@return         ������ true / ���s�� false
		@exception      none
		*/
		bool Initialize(HINSTANCE, HWND);
		/*
		@brief          �X�V����
		@param          none
		@return         ������ true/���s�� false
		@exception      none
		*/
		bool Read();
		/*
		@brief          �L�[��������Ă��邩
		@param          DIK_�n�̃L�[�R�[�h
		@return         true/false
		@exception      none
		*/
		bool IsKeyDown(unsigned int keyType);
		/*
		@brief          �f�o�C�X���̉������
		@param          none
		@return         none
		@exception      none
		*/
		void Finalize();
		/*
		@brief          �R���g���[���[����������E�B���h�E��ύX����
		@param          �E�B���h�E�n���h��
		@return         none
		@exception      none
		*/
		void ChangeActiveWindow(HWND hwnd);

	private:
		IDirectInput8* m_directInput;
		IDirectInputDevice8* m_keybord;
		unsigned char m_keybordState[256];
	};
}
#endif