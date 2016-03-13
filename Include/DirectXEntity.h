#ifndef _DIRECTXENTITY_H
#define _DIRECTXENTITY_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      DirectXEntity.h
@brief     Direct3D�̃A�h���X��ێ�
           �`�悷��I�u�W�F�N�g�Ȃǂ͂��̃N���X���p������

*******************************************************************************
@date       2015/12/23
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/23 ���{�q
-# Initial Version
******************************************************************************/
#include "Direct3DManager.h"
namespace aetherClass{
	class DirectXEntity
	{
		public:
			DirectXEntity();
			~DirectXEntity();
		

			/*
			@brief          Direct3DManager�̃A�h���X���R�s�[���ێ�
			@param[in]      manager Direct3DManager�^�̃|�C���^
			@param[in]      �K�p����E�B���h�E�n���h��
			@return         none
			@exception      none
			*/
			static void CopyDirectX(Direct3DManager* manager,WindowBase** window,UINT numWindow);

			/*
			@brief          Direct3DManager�̎Q�Ƃ�Ԃ�
			@param[in]      manager Direct3DManager�^�̃|�C���^
			@par            Refer
			- �Q�Ƃ��郁���o�ϐ�   m_direct3d
			@par            Modify
			- �ύX���郁���o�ϐ�   none
			@return         none
			@exception      none
			*/
			Direct3DManager* GetDirect3DManager()const;


			/*
			@brief          �E�B���h�E�n���h���̎Q�Ƃ�Ԃ�
			@param[in]      �E�B���h�E�ԍ�
			@return         HWND
			@exception      none
			*/
			HWND& GetWindowHandle(std::wstring)const;

			/*
			@brief          �擪�̃E�B���h�E�n���h���̎Q�Ƃ�Ԃ�
			@param[in]      none
			@return         HWND
			@exception      none
			*/
			HWND& GetWindowHandle()const;



		private:
			static Direct3DManager* m_direct3d;
			static std::unordered_map<std::wstring, WindowBase*>m_window;

	};
}
#endif