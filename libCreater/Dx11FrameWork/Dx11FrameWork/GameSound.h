/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameSound.h
@brief     �T�E���h���g�p����ۂɎg�p����N���X

*******************************************************************************
@date       2015/12/23
@author     ���{�q
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
		@brief          �t�@�C���̓ǂݍ���
		@param[in]      �t�@�C�������܂񂾃p�X
		@return         �������Ftrue
		@exception      none
		*/
		bool Load(const char*);

		/*
		@brief          �{�����[���̐ݒ�
		@param[in]      float�l
		@return         none
		@exception      none
		*/
		void SetValume(const float);

		/*
		@brief          �X�s�[�h�̐ݒ�
		@param[in]      eSoundSpeed�i�񋓌^�j�̂����ꂩ�̒l
		@return         none
		@exception      none
		*/
		void SetSpeed(long);

		/*
		@brief          ��񂫂�̍Đ��p
		@param          none
		@return         �������Ftrue
		@exception      none
		*/
		bool PlayToOneTime();

		/*
		@brief          ���[�v�Đ��p
		@param          none
		@return         �������Ftrue
		@exception      none
		*/
		bool PlayToLoop();
		
		/*
		@brief          �ꎞ��~�p
		@param          none
		@return         none
		@exception      none
		*/
		void Stop();

		/*
		@brief          ���[�h�ɐ����������ǂ���
		@param          
		@return         �������Ă����true
		@exception      none
		*/
		bool IsLoadSuccess();

		/*
		@brief          �Đ����I���������ǂ���
		@param          
		@return         �I�����Ă����true
		@exception      none
		*/
		bool IsPlayEnd();
	private:
	
		/*
		@brief          ����p
		@param          none
		@return         none
		@exception      none
		*/
		void Finalize();
		
		/*
		@brief          DirectSound�̏������p
		@param          none
		@return         �������Ftrue
		@exception      none
		*/
		bool InitializeDirectSound();

		/*
		@brief          DirectSound�̉���p
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeDIrectSound();

		/*
		@brief          Wave�t�H�[�}�b�g�̃t�@�C���̓ǂݍ���
		@param          none
		@return         none
		@exception      none
		*/
		bool LoadWaveFile(const char*, IDirectSoundBuffer8**);

		/*
		@brief          Wave�t�H�[�}�b�g�̃t�@�C���̉���p
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeWaveFile(IDirectSoundBuffer8**);

		/*
		@brief          �Đ��p
		@param          none
		@return         �������Ftrue
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