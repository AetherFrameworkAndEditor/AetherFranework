/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameSound.h
@brief     サウンドを使用する際に使用するクラス

*******************************************************************************
@date       2015/12/23
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _GAMESOUND_H
#define _GAMESOUND_H

#ifndef _SOUNDLINK_
#define _SOUNDLINK_
#pragma comment (lib,"dsound.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"winmm.lib")
#endif

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#include "DirectXEntity.h"

#define HIGH_SPEED 44100
#define LOW_SPEED 172

namespace aetherClass{
	enum eSoundSpeed{
		eHighSpeed = 44100,
		eSecondSpeed = 22050,
		eThirdSpeed = 11025,
		eFourthSpeed = 5512,
		eFifthSpeed = 2756,
		eSixthSpeed = 1378,
		eSeventhSpeed = 689,
		eEighthSpeed = 344,
		eLowSpeed = 172,
		eNull = 0
	};

	class GameSound:
		DirectXEntity
	{

	private:
		struct WaveHeaderType{
			char _chunkID[4];
			unsigned long _chunkSize;
			char _format[4];
			char _subChunkID[4];
			unsigned long _subChunkSize;
			unsigned short _audioFormat;
			unsigned short _numChannels;
			unsigned long _sampleRate;
			unsigned long _bytesPerSecound;
			unsigned short _blockAign;
			unsigned short _bitsPerSample;
			char _dataChunkID[4];
			unsigned long _dataSize;
		};

	public:
		GameSound();
		~GameSound();
		
		
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

		/*
		@brief          ロードに成功したかどうか
		@param          
		@return         成功していればtrue
		@exception      none
		*/
		bool IsLoadSuccess();

		/*
		@brief          再生が終了したかどうか
		@param          
		@return         終了していればtrue
		@exception      none
		*/
		bool IsPlayEnd();
	private:
	
		/*
		@brief          解放用
		@param          none
		@return         none
		@exception      none
		*/
		void Finalize();
		
		/*
		@brief          DirectSoundの初期化用
		@param          none
		@return         成功時：true
		@exception      none
		*/
		bool InitializeDirectSound();

		/*
		@brief          DirectSoundの解放用
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeDIrectSound();

		/*
		@brief          Waveフォーマットのファイルの読み込み
		@param          none
		@return         none
		@exception      none
		*/
		bool LoadWaveFile(const char*, IDirectSoundBuffer8**);

		/*
		@brief          Waveフォーマットのファイルの解放用
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeWaveFile(IDirectSoundBuffer8**);

		/*
		@brief          再生用
		@param          none
		@return         成功時：true
		@exception      none
		*/
		bool PlayWaveFile(DWORD);


	private:
		IDirectSound8* m_directSound;
		IDirectSoundBuffer* m_primaryBuffer;

		IDirectSoundBuffer8* m_secondaryBuffer1;
	};
}
#endif