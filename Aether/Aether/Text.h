
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Text.h
@brief     �����`��p�N���X
*******************************************************************************
@date       2016/2/20
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/

#ifndef _TEXTFIELD_H
#define _TEXTFIELD_H

#include"Font.h"
#include"Rectangle2D.h"
#include<crtdbg.h>
#include<string>
#include<map>

namespace aetherClass{
	class Text : 
		public Rectangle2D
	{
	public:
		Text();
		~Text();

		/*
		@brief          ������̍X�V
		@param			�\��������������
		@return         ������ true/���s�� false
		@exception      none
		*/
		bool UpdateText(std::wstring);

		/*
		@brief          �t�H���g�̐ݒ�
		@param[in]      �t�H���g
		@return         none
		@exception      none
		*/
		void SetFont(Font*);

	private:
		/*
		@brief          �萔�o�b�t�@�̐ݒ�
		@param[in]      none
		@return         none
		@exception      none
		*/
		void CreateConstantBuffers()override;
		Font *m_font;
		ID3D11ShaderResourceView *m_fontTexture;
		Texture *m_sampler;
		
	};
}
#endif