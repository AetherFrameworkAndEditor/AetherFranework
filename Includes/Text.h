
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Text.h
@brief     文字描画用クラス
*******************************************************************************
@date       2016/2/20
@author     金子和樹
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
		@brief          文字列の更新
		@param			表示したい文字列
		@return         成功時 true/失敗時 false
		@exception      none
		*/
		bool UpdateText(std::wstring);

		/*
		@brief          フォントの設定
		@param[in]      フォント
		@return         none
		@exception      none
		*/
		void SetFont(Font*);

	private:
		/*
		@brief          定数バッファの設定
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