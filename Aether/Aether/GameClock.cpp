#include "GameClock.h"
#include <Windows.h>
#include <iostream>
using namespace aetherClass;


std::chrono::system_clock::time_point GameClock::m_beginTime;
float GameClock::m_perSeconds = 60.0f;
float GameClock::m_deltaTime = 0.0f;
GameClock::GameClock()
{
	m_deltaTime = 1000.0f / m_perSeconds;
}


GameClock::~GameClock()
{
}

//
void GameClock::BeginTime(){

	m_beginTime = std::chrono::system_clock::now();
	return;
}

//
void GameClock::EndTime(){
	
	auto endTime = std::chrono::system_clock::now();

	// 1ƒtƒŒ[ƒ€‚ÌŠÔ‚Ì·•ª‚ğƒ~ƒŠ•b‚Åæ“¾
	float tick = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_beginTime).count();
	
	// ƒ~ƒŠ•b‚©‚ç•b‚É•ÏŠ·
	float perSecond = 1000.0f / m_perSeconds;

	// ‚±‚±‚ÅdeltaTime‚ğ‹‚ß‚é
	m_deltaTime = ((perSecond - (tick/1000.f))/1000.f);

	std::cout << m_deltaTime << std::endl;
	return;
}

//
double GameClock::GetDeltaTime(){
	return m_deltaTime;
}


//
void GameClock::SetPerSeconds(float fps){
	m_perSeconds = fps;
	m_deltaTime = 1.0f / m_perSeconds;

	return;
}