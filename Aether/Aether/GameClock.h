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
		@brief          ���݂̃Q�[�������Ԃ̎擾
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