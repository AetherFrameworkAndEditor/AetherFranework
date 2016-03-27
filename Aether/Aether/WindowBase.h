/******************************************************************************/
/*! @addtogroup aetherClass
@file      WindowBase.h
@brief     Window�쐬����ۂɊ��N���X�Ƃ��Ďg�p����N���X

*******************************************************************************
@date       2016/3/12
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/

#ifndef _WINDOWBASE_H
#define _WINDOWBASE_H

#include<Windows.h>
#include<string>
#include"Vector2.h"

namespace aetherClass{
	
	class WindowBase
	{
	public:
		/*
			�g���E�B���h�E���̃X�^�C����ύX�������ꍇ���p����
			SetWindowStyle��Create����Ɏ��s���邱��
			�t���O�̏ڍׂ�Microsoft��
		*/
		struct WindowStyleDesc
		{
			WindowStyleDesc(){
				_classStyle = CS_HREDRAW | CS_VREDRAW;
				_windowStyle = WS_OVERLAPPED | WS_SYSMENU;
				_windowStyleEx = WS_EX_APPWINDOW;
				_parent = NULL;
				_menu = NULL;
			}
			UINT _classStyle;
			DWORD _windowStyleEx, _windowStyle;
			HWND _parent;
			HMENU _menu;
		};
	public:
		WindowBase();
		~WindowBase();

		/*
		@brief          �E�B���h�E�n���h���𓾂�
		@param          none
		@return         �E�B���h�E�n���h��
		*/
		HWND GetWindowHandle();

		/*
		@brief          �E�B���h�E���𓾂�
		@param          none
		@return         �E�B���h�E��
		*/
		std::wstring GetWindowName();
	
		/*
		@breaf	�g���E�B���h�E���̃X�^�C����ύX�������ꍇ���p����
				SetWindowStyle��Create����Ɏ��s���邱��
				�t���O�̏ڍׂ�Microsoft��
		@param          WindowStyleDesc
		@return         none
		*/
		void SetWindowStyles(WindowBase::WindowStyleDesc windowStyleDesc);

		/*
		@brief          �E�B���h�E�𐶐�����B
		@param          �E�B���h�E���i���ʎq�j
		@param          �T�C�Y
		@param          �\���ʒu
		@return         ���������@true/���s false
		@exception		�f�o�b�O��	ASSERT_Message
		*/
		bool Create(std::wstring windowName, Vector2 screenSize, Vector2 pos = { 0, 0 });

	private:

		BOOL RegisterWindow(std::wstring windowName);
		static LRESULT CALLBACK CloseWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		bool InitializeWindow(Vector2 screenSize, Vector2 screenPos);
		
		/*
		@brief          �E�B���h�E�v���V�[�W�� �p���������ɓƎ��̏�����ǉ�����
		@return         callback
		@exception		none
		*/
		virtual LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		/*
		@brief          �E�B���h�E������̏���������
		@return         none
		@exception		none
		*/
		virtual void OnCreate(){};

	protected:
		HWND m_hWnd;
		std::wstring m_windowName;
		WindowStyleDesc	m_styleDesc;

	};

}

#endif