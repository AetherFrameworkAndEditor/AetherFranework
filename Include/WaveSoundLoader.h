#ifndef _WAVESOUNDLOADER_H
#define _WAVESOUNDLOADER_H
#include <XAudio2.h>
#include <vector>
#include <string>
namespace aetherClass{
	class WaveSoundLoader
	{
	public:
		WaveSoundLoader();
		~WaveSoundLoader();

		/*
		@brief          �ǂݍ��ݏ���
		@param          �t�@�C����
		@return         �������Ftrue/���s���Ffalse
		@exception      none
		*/
		bool Load(const std::string& filleName);

		/*
		@brief          �t�@�C�����̎擾
		@param          none
		@return         �t�@�C����
		@exception      none
		*/
		const std::string& GetFileName()const;

		/*
		@brief          �t�H�[�}�b�g�̎擾
		@param          none
		@return         WAVEFORMATEX�\���̂ւ̎Q��
		@exception      none
		*/
		const WAVEFORMATEX& GetWaveFormatEx()const;

		/*
		@brief          WAVE�f�[�^�̎擾
		@param          none
		@return         WAVEFORMATEX�\���̂ւ̎Q��
		@exception      none
		*/
		const BYTE* GetWaveData()const;

		/*
		@brief          �f�[�^�T�C�Y�̎擾
		@param          none
		@return         �f�[�^�T�C�Y
		@exception      none
		*/
		const size_t GetWaveSize()const;
	private:
		
		/*
		@brief          �t�@�C���I�[�v��
		@param          �t�@�C����
		@return         none
		@exception      none
		*/
		bool Open(const std::string& fileName);

		/*
		@brief          �t�@�C���N���[�Y
		@param          none
		@return         none
		@exception      none
		*/
		void Close();

		/*
		@brief          WAVEFORMATEX�\���̂Ƀf�[�^�𑗂�
		@param          none
		@return         none
		@exception      none
		*/
		bool ReadToWaveFmtEx(); 

		/*
		@brief          Wave�f�[�^��ǂݎ��
		@param          none
		@return         none
		@exception      none
		*/
		bool ReadToWaveData();

		/*
		@brief          �w�b�_�����邩�̊m�F
		@param          none
		@return         none
		@exception      none
		*/
		bool CheckWaveHeader();

		/*
		@brief          FMT �`�����N�����邩�̊m�F
		@param          none
		@return         none
		@exception      none
		*/
		bool CheckFMTChunk();

		/*
		@brief          DATA �`�����N�����邩�̊m�F
		@param          none
		@return         none
		@exception      none
		*/
		bool CheckDATAChunk();

	private:
		HMMIO m_hMmio;    // MMIO�n���h��
		MMIOINFO m_mmioInfo;
		MMCKINFO m_RIFTChunk;   // RIFT�`�����N
		MMCKINFO m_FMTChunk;    // FMT�`�����N
		MMCKINFO m_DATAChunk;   // DATA�`�����N
		WAVEFORMATEX m_waveFormatEx;   // WAVE �t�H�[�}�b�g�\����
		std::vector<BYTE> m_waveData;  // ���y�f�[�^�i�[�R���e�i
		std::string m_fileName;
	};
}
#endif