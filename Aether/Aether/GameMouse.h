#ifndef _GAMEMOUSE_H
#define _GAMEMOUSE_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameMouse.h
@brief     �}�E�X�Ɋւ��鏈��

*******************************************************************************
@date       2016/2/28
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu
*******************************************************************************/
#include"DirectXEntity.h"
#include<dinput.h>
#include"ViewCamera.h"
#include"Vector3.h"
#include<string>
#include"Line.h"
#ifndef _CONTROLLER_
#define _CONTROLLER_
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#endif
namespace aetherClass{
	class GameMouse 
		: private DirectXEntity
	{
	public:
		GameMouse();
		~GameMouse();

	public:
		/*
		@brief          �f�o�C�X�̏�����
		@param          �C���X�^���X�n���h��
		@param          �E�B���h�E�n���h��
		@return         ������ true / ���s�� false
		@exception      none
		*/
		bool Initialize(HINSTANCE&, HWND&);

		/*
		@brief          �}�E�X���Ԃ̍X�V
		@param          none
		@return         ������ true / ���s�� false
		@exception      none
		*/
		bool Frame();

		/*
		@brief          �f�o�C�X���̉������
		@param          none
		@return         none
		@exception      none
		*/
		void Finalize();

		/*
		@brief          �J�[�\���摜��ς�����
		@param          �t�@�C����
		@return         none
		@exception      none
		*/
		void SetCursor(std::wstring);

		/*
		@brief          ���N���b�N������Ă��邩�i�������j
		@param          none
		@return         true/false
		@exception      none
		*/
		bool IsLeftButtonDown();
		/*
		@brief          �E�N���b�N������Ă��邩�i�������j
		@param          none
		@return         true/false
		@exception      none
		*/
		bool IsRightButtonDown();
		/*
		@brief          ���N���b�N������Ă��邩�i�������j
		@param          none
		@return         true/false
		@exception      none
		*/
		bool IsWheelDown();

		/*
		@brief          ���N���b�N������Ă��邩�i�P��̂݁j
		@param          none
		@return         true/false
		@exception      none
		*/
		bool IsLeftButtonTrigger();
		/*
		@brief          �E�N���b�N������Ă��邩�i�P��̂݁j
		@param          none
		@return         true/false
		@exception      none
		*/
		bool IsRightButtonTrigger();
		/*
		@brief          ���N���b�N������Ă��邩�i�P��̂݁j
		@param          none
		@return         true/false
		@exception      none
		*/
		bool IsWheelTrigger();

		/*
		@brief          �}�E�X���W�����[���h�֕ϊ����鏈�����s��
		@param          ViewCamera
		@return         RayVector�^�̕ϐ�
		@exception      none
		*/
		RayVector Intersection(ViewCamera);
		/*
		@brief          �R���g���[���[����������E�B���h�E��ύX����
		@param          �E�B���h�E�n���h��
		@return         none
		@exception      none
		*/
		void ChangeActiveWindow(HWND hwnd);
		/*
		@brief          �z�C�[���̉�]�����擾����
		@param          none
		@return         �z�C�[����]��
		@exception      none
		*/
		float GetWheelMovement();
		/*
		@brief          �}�E�X�̈ړ��ʂ��擾����i���W�ł͂Ȃ��j
		@param          none
		@return         �}�E�X�̈ړ���
		@exception      none
		*/
		Vector2 GetMouseMovement();
		/*
		@brief          �}�E�X�̉�ʍ��W���擾����
		@param          none
		@return         �}�E�X�̍��W
		@exception      none
		*/
		Vector2 GetMousePosition();

	private:
		/*
		@brief          �X�V����
		@param          none
		@return         ������ true/���s�� false
		@exception      none
		*/
		bool Read();

	private:
		HWND m_hWnd;
		IDirectInput8* m_directInput;
		IDirectInputDevice8* m_mouse;

		DIMOUSESTATE m_mouseState;

		POINT m_screen;
		POINT m_mousePoint;

	};
}
#endif