#ifndef _FONT_H
#define _FONT_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file       Font.h
@brief     Font���Ǘ�����N���X

*******************************************************************************
@date       2016/2/11
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/

#include<string>
#include<crtdbg.h>
#include<Windows.h>

namespace aetherClass{
	/*
	TrueTypeFont(.ttf)�̏ꍇ�̐ݒ��Default�ɂ��Ă��܂�
	fontSize		�t�H���g�T�C�Y
	fontName		�t�H���g��
	charSet			�t�H���g�̕����Z�b�g
	fileName		�t�@�C���p�X
	���Œ���ݒ肵�Ă�������

	�ڂ���������
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
		int _fontSize;	//�t�H���g�T�C�Y
		int _width;		//������
		int _escapement;	//������������̊p�x
		int _orientation;	//�x�[�X���C���̊p�x
		int _fontThick;		//�����̑���0~1000
		DWORD _itatic;		//�Α� True or False
		DWORD _underLine;	//���� True or False
		DWORD _strikeOut;	//�������� True or False
		DWORD _charSet;		//�����Z�b�g�̎��ʎq
		DWORD _outputPrecision;	//�o�͐��x
		DWORD _clipPrecision;	//�N���b�s���O���x
		DWORD _quality;			//�i��
		DWORD _pitchAndFamily;	//�s�b�`�ƃt�@�~��
		std::wstring _fontName;		//�t�H���g��
		std::wstring _fileName;		//�t�@�C����
		
	};

	class Font
	{
	public:
		Font();
		~Font();

		/*
		@brief          �t�H���g��ǂݍ���
		@param[in]      �ǂݍ��ݎ��̐ݒ�
						�ڍׂ�FontDesc��
		@return         �^/�U
		*/
		bool Load(FontDesc& fontDesc);
		
		/*
		@brief          �ǂݍ��񂾃t�H���g�̉��
		@param[in]      none
		@return         none
		*/
		void Release();

		/*
		@brief          �t�H���g�̎擾
		@param[in]      none
		@return         �t�H���g�̃n���h��
		*/
		HFONT GetFont();
	private:
		FontDesc m_fontDesc;
		HFONT m_hFont;
	};


}
#endif