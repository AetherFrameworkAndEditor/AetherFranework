
/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameClock.h
@brief     �Q�[�������ԊǗ��p�N���X�B����̓f���^�^�C�����擾�\

*******************************************************************************
@date       2015/12/23
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _GAMECLOCK_H
#define _GAMECLOCK_H
#include <chrono>
namespace aetherClass{
	class GameClock
	{
	public:

		/*
		@brief          �ŏ��̔�r�̂��߂̎��Ԃ̐ݒ�
		                ��{�I�Ɏg��Ȃ��ł�������
		@param[in]		none
		@return         none
		@exception      none
		*/
		static void BeginTime();

		/*
		@brief          �f���^�^�C���̎擾
		@param[in]		none
		@return         none
		@exception      none
		*/
		static double GetDeltaTime();

		/*
		@brief          ���Ԃ̍X�V
		�@�@�@�@�@�@�@�@�@��{�I�Ɏg��Ȃ��ł�������
		@param[in]		none
		@return         none
		@exception      none
		*/
		static void EndTime();

		/*
		@brief          �t���[�����[�g�̐ݒ�B�����ł�60�ɐݒ�
		@param[in]		none
		@return         none
		@exception      none
		*/
		static void SetPerSeconds(float);
	private:
		GameClock();
		~GameClock();
	private:
		static std::chrono::system_clock::time_point m_beginTime;
		static float m_perSeconds;
		static float m_deltaTime;
	};
}
#endif