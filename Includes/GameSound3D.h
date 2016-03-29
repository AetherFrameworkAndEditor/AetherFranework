
/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameSound3D.h
@brief     3D�T�E���h���g�p����ۂɎg�p����N���X

*******************************************************************************
@date       2015/12/23
@author     ���{�q
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
		@brief          �Đ��ʒu�̐ݒ�
		@param[in]      Vector3�l
		@return         none
		@exception      none
		*/
		void SetPosition(Vector3);


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


	private:
		/*
		@brief          ����p
		@param          none
		@return         none
		@exception      none
		*/
		void Finalize();
		
		/*
		@brief          DirectSound�������p
		@param          none
		@return         none
		@exception      none
		*/
		bool InitializeDirectSound();
		
		/*
		@brief          DirectSound����p
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeDirectSound();

		/*
		@brief          Wave�t�H�[�}�b�g�̃f�[�^�������p
		@param          none
		@return         none
		@exception      none
		*/
		bool LoadWaveFile(const char*, IDirectSoundBuffer8**, IDirectSound3DBuffer8**);

		/*
		@brief          Wave�t�H�[�}�b�g�̃f�[�^����p
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeWaveFile(IDirectSoundBuffer8**, IDirectSound3DBuffer8**);

		/*
		@brief          �Đ��p
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