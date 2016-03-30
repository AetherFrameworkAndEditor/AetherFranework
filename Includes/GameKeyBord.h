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
#include <Windows.h>

namespace{
	const int kMaxKeyType = 256;
}
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
		void Initialize();
		
		/*
		@brief          �L�[�������ꂽ��
		@param          �L�[�R�[�h
		@return         true/false
		@exception      none
		*/
		bool IsKeyDown(unsigned int);
		

		/*
		@brief          �L�[��������Ă��邩
		@param          �L�[�R�[�h
		*/
		void KeyDown(unsigned int keyType);

		/*
		@brief          �L�[��������ė����ꂽ��
		@param          �L�[�R�[�h
		@exception      none
		*/
		void KeyUp(unsigned int keyType);
	private:
		bool m_keybordState[256];
	};
}
#endif