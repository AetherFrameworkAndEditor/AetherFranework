#ifndef _FONT_H
#define _FONT_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file       Font.h
@brief     Fontを管理するクラス

*******************************************************************************
@date       2016/2/11
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/

#include<string>
#include<crtdbg.h>
#include<Windows.h>

namespace aetherClass{
	/*
	TrueTypeFont(.ttf)の場合の設定をDefaultにしています
	fontSize		フォントサイズ
	fontName		フォント名
	charSet			フォントの文字セット
	fileName		ファイルパス
	を最低限設定してください

	詳しい説明は
	https://msdn.microsoft.com/ja-jp/library/cc428368.aspx
	*/
	struct FontDesc{
		FontDesc(){
			SecureZeroMemory(this, sizeof(FontDesc));
			_charSet = SHIFTJIS_CHARSET;
			_outputPrecision = OUT_TT_ONLY_PRECIS;
			_clipPrecision = CLIP_DEFAULT_PRECIS;
			_quality = PROOF_QUALITY;
			_pitchAndFamily = FIXED_PITCH | FF_MODERN;
		}
		int _fontSize;	//フォントサイズ
		int _width;		//文字幅
		int _escapement;	//文字送り方向の角度
		int _orientation;	//ベースラインの角度
		int _fontThick;		//文字の太さ0~1000
		DWORD _itatic;		//斜体 True or False
		DWORD _underLine;	//下線 True or False
		DWORD _strikeOut;	//取り消し線 True or False
		DWORD _charSet;		//文字セットの識別子
		DWORD _outputPrecision;	//出力精度
		DWORD _clipPrecision;	//クリッピング精度
		DWORD _quality;			//品質
		DWORD _pitchAndFamily;	//ピッチとファミリ
		std::wstring _fontName;		//フォント名
		std::wstring _fileName;		//ファイル名
		
	};

	class Font
	{
	public:
		Font();
		~Font();

		/*
		@brief          フォントを読み込む
		@param[in]      読み込み時の設定
						詳細はFontDescへ
		@return         真/偽
		*/
		bool Load(FontDesc& fontDesc);
		
		/*
		@brief          読み込んだフォントの解放
		@param[in]      none
		@return         none
		*/
		void Release();

		/*
		@brief          フォントの取得
		@param[in]      none
		@return         フォントのハンドル
		*/
		HFONT GetFont();
	private:
		FontDesc m_fontDesc;
		HFONT m_hFont;
	};


}
#endif