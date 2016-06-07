#ifndef _GAMEJOYPAD_H
#define _GAMEJOYPAD_H
#include <string>
#include <unordered_map>

namespace aetherClass{
	// �p�b�h�p
#ifndef KEY_TYPE
#define KEY_TYPE

// �W���C�p�b�h(���X�e�B�b�N,�E�X�e�B�b�N)
enum class eJoyStick{
	// ��
	eLUp,
	eLDown,
	eLLeft,
	eLRight,

	// �E
	eRUp,
	eRDown,
	eRLeft,
	eRRight,

	eNull
};

// �{�^��
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

		// �L�[���͂�����^�C�~���O�ŌĂ�
		void ReadKey();

		bool IsButtonDown(eJoyButton);
		bool ButtonPress(eJoyButton);
		bool ButtonRelease(eJoyButton);

		/*
			0�ȊO�̒l���Z�b�g����ƃR���g���[���[�̐U�����J�n����
			�l�͈̔́@0-65535
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