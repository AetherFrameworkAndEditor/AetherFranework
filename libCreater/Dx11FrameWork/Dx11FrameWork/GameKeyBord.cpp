#include "GameKeyBord.h"

using namespace aetherClass;
GameKeyBord::GameKeyBord(){}


GameKeyBord::~GameKeyBord()
{
	Initialize();
}

//
void GameKeyBord::Initialize(){
	for (int id = 0; id < kMaxKeyType; ++id)
	{
		m_keybordState[id] = false;
	}

	return;
}

//
void GameKeyBord::KeyDown(unsigned int keyType){
	m_keybordState[keyType] = true;

	return;
}

//
void GameKeyBord::KeyUp(unsigned int keyType){
	m_keybordState[keyType] = false;

	return;
}

bool GameKeyBord::IsKeyDown(unsigned int keyType)
{
	return m_keybordState[keyType];
}
