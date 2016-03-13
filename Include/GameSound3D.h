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
		bool Load(const char*);
		void SetValume(const float);
		void SetSpeed(long);
		void SetPosition(Vector3);
		bool PlayToOneTime();
		bool PlayToLoop();
		void Stop();



	private:
		void Finalize();
		bool InitializeDirectSound();
		void ShutdownDirectSound();

		bool LoadWaveFile(const char*, IDirectSoundBuffer8**, IDirectSound3DBuffer8**);
		void ShutdownWaveFile(IDirectSoundBuffer8**, IDirectSound3DBuffer8**);

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