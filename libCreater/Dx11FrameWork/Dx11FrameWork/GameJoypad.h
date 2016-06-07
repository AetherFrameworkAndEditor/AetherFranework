#ifndef _GAMEJOYPAD_H
#define _GAMEJOYPAD_H
#include <string>
#include <unordered_map>

namespace aetherClass{
	// パッド用
#ifndef KEY_TYPE
#define KEY_TYPE

// ジョイパッド(左スティック,右スティック)
enum class eJoyStick{
	// 左
	eLUp,
	eLDown,
	eLLeft,
	eLRight,

	// 右
	eRUp,
	eRDown,
	eRLeft,
	eRRight,

	eNull
};

// ボタン
enum class eJoyButton{
	eUp,
	eDown,
	eLeft,
	eRight,

	eA,
	eB,
	eX,
	eY,
	eLB1,
	eRB1,

	eStart,
	eBack,
	eNull
};

#endif // !KEY_TYPE

	class GameJoypad
	{
	public:

		
		GameJoypad();
		~GameJoypad();
		bool Initialize();

		// キー入力をするタイミングで呼ぶ
		void ReadKey();

		bool IsButtonDown(eJoyButton);
		bool ButtonPress(eJoyButton);
		bool ButtonRelease(eJoyButton);

		/*
			0以外の値をセットするとコントローラーの振動が開始する
			値の範囲　0-65535
			first : Left
			second : Right
		*/
		void SetVibration(std::pair<unsigned int, unsigned int> vib);
	private:
		std::unordered_map<eJoyButton, bool> m_buttonList;
		std::unordered_map<eJoyButton, bool> m_prevButtonList;

	};
}
#endif