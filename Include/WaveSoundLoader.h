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
		@brief          読み込み処理
		@param          ファイル名
		@return         成功時：true/失敗時：false
		@exception      none
		*/
		bool Load(const std::string& filleName);

		/*
		@brief          ファイル名の取得
		@param          none
		@return         ファイル名
		@exception      none
		*/
		const std::string& GetFileName()const;

		/*
		@brief          フォーマットの取得
		@param          none
		@return         WAVEFORMATEX構造体への参照
		@exception      none
		*/
		const WAVEFORMATEX& GetWaveFormatEx()const;

		/*
		@brief          WAVEデータの取得
		@param          none
		@return         WAVEFORMATEX構造体への参照
		@exception      none
		*/
		const BYTE* GetWaveData()const;

		/*
		@brief          データサイズの取得
		@param          none
		@return         データサイズ
		@exception      none
		*/
		const size_t GetWaveSize()const;
	private:
		
		/*
		@brief          ファイルオープン
		@param          ファイル名
		@return         none
		@exception      none
		*/
		bool Open(const std::string& fileName);

		/*
		@brief          ファイルクローズ
		@param          none
		@return         none
		@exception      none
		*/
		void Close();

		/*
		@brief          WAVEFORMATEX構造体にデータを送る
		@param          none
		@return         none
		@exception      none
		*/
		bool ReadToWaveFmtEx(); 

		/*
		@brief          Waveデータを読み取る
		@param          none
		@return         none
		@exception      none
		*/
		bool ReadToWaveData();

		/*
		@brief          ヘッダがあるかの確認
		@param          none
		@return         none
		@exception      none
		*/
		bool CheckWaveHeader();

		/*
		@brief          FMT チャンクがあるかの確認
		@param          none
		@return         none
		@exception      none
		*/
		bool CheckFMTChunk();

		/*
		@brief          DATA チャンクがあるかの確認
		@param          none
		@return         none
		@exception      none
		*/
		bool CheckDATAChunk();

	private:
		HMMIO m_hMmio;    // MMIOハンドル
		MMIOINFO m_mmioInfo;
		MMCKINFO m_RIFTChunk;   // RIFTチャンク
		MMCKINFO m_FMTChunk;    // FMTチャンク
		MMCKINFO m_DATAChunk;   // DATAチャンク
		WAVEFORMATEX m_waveFormatEx;   // WAVE フォーマット構造体
		std::vector<BYTE> m_waveData;  // 音楽データ格納コンテナ
		std::string m_fileName;
	};
}
#endif