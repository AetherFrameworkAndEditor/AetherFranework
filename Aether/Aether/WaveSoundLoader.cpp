#include "WaveSoundLoader.h"
#include <assert.h>
#include <XAudio2.h>
#include <mmsystem.h>
#ifndef _SOUND_
#define _SOUND_
#pragma comment (lib,"winmm.lib")
#include <fbxsdk.h>
#endif

using namespace aetherClass;

namespace{
	const int kReadError = -1;
}

WaveSoundLoader::WaveSoundLoader()
{
	m_hMmio = NULL;
	m_mmioInfo = { NULL };
	m_waveFormatEx = { NULL };

	m_waveData.clear();
}


WaveSoundLoader::~WaveSoundLoader()
{
	Close();
}

bool WaveSoundLoader::Open(const std::string& fileName){
	m_fileName = fileName;

	std::vector<char> copyFileName(fileName.begin(), fileName.end());
	copyFileName.push_back('\0');

	m_mmioInfo = { NULL };

	if (!(m_hMmio = mmioOpen(LPWSTR(copyFileName[0]), &m_mmioInfo, MMIO_READ)))
	{
		assert(!"�t�@�C���ǂ߂Ȃ�����");
		return false;
	}
	return true;
}

//
void WaveSoundLoader::Close(){
	if (::mmioClose(m_hMmio, 0) == MMIOERR_CANNOTWRITE)
	{
		assert(!"�t�@�C�������");
		return;
	}

	return;
}

//
bool WaveSoundLoader::CheckWaveHeader(){
	m_RIFTChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');

	if (::mmioDescend(m_hMmio, &m_RIFTChunk, NULL, MMIO_FINDRIFF) != MMSYSERR_NOERROR)
	{
		// �w�b�_���Ȃ�
		return false;
	}
	return true;
}

//
bool WaveSoundLoader::CheckFMTChunk(){
	m_FMTChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');

	if (mmioDescend(m_hMmio, &m_FMTChunk, &m_RIFTChunk, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		// FMT �`�����N���Ȃ�
		return false;
	}
	return true;
}

//
bool WaveSoundLoader::CheckDATAChunk(){
	m_DATAChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');

	if (::mmioDescend(m_hMmio, &m_DATAChunk, &m_RIFTChunk, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		// DATA �`�����N���Ȃ�
		return false;
	}
	return true;
}

//
bool WaveSoundLoader::ReadToWaveFmtEx(){
	LONG readSize = ::mmioRead(m_hMmio, reinterpret_cast<HPSTR>(&m_waveFormatEx), m_FMTChunk.cksize);
	switch (readSize)
	{
		//-----------------------------------------------------
	case kReadError:
		assert(!"missing reading wave file");
		break;
		//-----------------------------------------------------
	default:
		// �f�[�^�T�C�Y�������Ă邩�`�F�b�N����
		if (readSize != m_FMTChunk.cksize)
		{
			assert(!"not match data size");
			return FALSE;
		}
	}
	return true;
}

//
bool WaveSoundLoader::ReadToWaveData(){
	// WAVE�f�[�^�p�Ƀ��T�C�Y
	m_waveData.resize(m_DATAChunk.cksize);

	if (::mmioRead(m_hMmio, reinterpret_cast<HPSTR>(&m_waveData[0]), m_DATAChunk.cksize) != m_DATAChunk.cksize)
	{
		assert(!"not match data size");
	}

	return true;
}

//
bool WaveSoundLoader::Load(const std::string &fileName){

	// �t�@�C�����J��
	if (!this->Open(fileName))
	{
		return false;
	}

	// �w�b�_�̊m�F
	if (!this->CheckWaveHeader())
	{
		return false;
	}

	// FMT �`�����N�̃`�F�b�N
	if (!this->CheckFMTChunk())
	{
		return false;
	}

	// WAVEFORMATEX�\���̂Ƀf�[�^�𑗂�
	if (!this->ReadToWaveFmtEx())
	{
		return false;
	}

	// �ǂݍ��݈ʒu��擪�ɖ߂�
	::mmioAscend(m_hMmio, &m_FMTChunk, SEEK_SET);

	// DATA�`�����N�̃`�F�b�N
	if (!this->CheckDATAChunk())
	{
		return false;
	}

	// WAVE�f�[�^��ǂ�
	if (!this->ReadToWaveData())
	{
		return false;
	}

	// �t�@�C�������
	this->Close();
}

//
const std::string& WaveSoundLoader::GetFileName()const{
	return m_fileName;
}

//
const WAVEFORMATEX& WaveSoundLoader::GetWaveFormatEx()const{
	return m_waveFormatEx;
}

//
const BYTE* WaveSoundLoader::GetWaveData()const{
	return &m_waveData[0];
}

//
const size_t WaveSoundLoader::GetWaveSize()const{
	return m_waveData.size();
}