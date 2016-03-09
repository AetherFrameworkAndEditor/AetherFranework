#ifndef _GAMECLOCK_H
#define _GAMECLOCK_H
#include <chrono>
namespace aetherClass{
	class GameClock
	{
	public:

		/*
		@brief          最初の比較のための時間の設定
		                基本的に使わないでください
		@param[in]		none
		@return         none
		@exception      none
		*/
		static void BeginTime();

		/*
		@brief          現在のゲーム内時間の取得
		@param[in]		none
		@return         none
		@exception      none
		*/
		static double GetDeltaTime();

		/*
		@brief          時間の更新
		　　　　　　　　　基本的に使わないでください
		@param[in]		none
		@return         none
		@exception      none
		*/
		static void EndTime();

		/*
		@brief          フレームレートの設定。初期では60に設定
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