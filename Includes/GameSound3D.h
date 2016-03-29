
/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameSound3D.h
@brief     3Dサウンドを使用する際に使用するクラス

*******************************************************************************
@date       2015/12/23
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _GAMESOUND3D_H_
#define _GAMESOUND3D_H_

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>

#include "DirectXEntity.h"
namespace aetherClass{
	class GameSound3D :
		DirectXEntity
	{
	private:
		struct WaveHeaderType
		{
			char chunkId[4];
			unsigned long chunkSize;
			char format[4];
			char subChunkId[4];
			unsigned long subChunkSize;
			unsigned short audioFormat;
			unsigned short numChannels;
			unsigned long sampleRate;
			unsigned long bytesPerSecond;
			unsigned short blockAlign;
			unsigned short bitsPerSample;
			char dataChunkId[4];
			unsigned long dataSize;
		};

	public:
		GameSound3D();
		~GameSound3D();
		
		/*
		@brief          ファイルの読み込み
		@param[in]      ファイル名を含んだパス
		@return         成功時：true
		@exception      none
		*/
		bool Load(const char*);

		/*
		@brief          ボリュームの設定
		@param[in]      float値
		@return         none
		@exception      none
		*/
		void SetValume(const float);

		/*
		@brief          スピードの設定
		@param[in]      eSoundSpeed（列挙型）のいずれかの値
		@return         none
		@exception      none
		*/
		void SetSpeed(long);


		/*
		@brief          再生位置の設定
		@param[in]      Vector3値
		@return         none
		@exception      none
		*/
		void SetPosition(Vector3);


		/*
		@brief          一回きりの再生用
		@param          none
		@return         成功時：true
		@exception      none
		*/
		bool PlayToOneTime();

		/*
		@brief          ループ再生用
		@param          none
		@return         成功時：true
		@exception      none
		*/
		bool PlayToLoop();

		/*
		@brief          一時停止用
		@param          none
		@return         none
		@exception      none
		*/
		void Stop();


	private:
		/*
		@brief          解放用
		@param          none
		@return         none
		@exception      none
		*/
		void Finalize();
		
		/*
		@brief          DirectSound初期化用
		@param          none
		@return         none
		@exception      none
		*/
		bool InitializeDirectSound();
		
		/*
		@brief          DirectSound解放用
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeDirectSound();

		/*
		@brief          Waveフォーマットのデータ初期化用
		@param          none
		@return         none
		@exception      none
		*/
		bool LoadWaveFile(const char*, IDirectSoundBuffer8**, IDirectSound3DBuffer8**);

		/*
		@brief          Waveフォーマットのデータ解放用
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeWaveFile(IDirectSoundBuffer8**, IDirectSound3DBuffer8**);

		/*
		@brief          再生用
		@param          none
		@return         none
		@exception      none
		*/
		bool PlayWaveFile(DWORD);

	private:
		IDirectSound8* m_directSound;
		IDirectSoundBuffer* m_primaryBuffer;
		IDirectSound3DListener8* m_listener;
		IDirectSoundBuffer8* m_secondaryBuffer1;
		IDirectSound3DBuffer8* m_secondary3DBuffer1;
		Vector3 m_position;
		bool m_isCompleate;
	};
}
#endif