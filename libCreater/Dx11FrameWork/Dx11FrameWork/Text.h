
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Text.h
@brief     文字描画用クラス
*******************************************************************************
@date       2016/1/10
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
		
		bool UpdateText(std::wstring);
		void SetFont(Font*);

	private:
		void CreateConstantBuffers()override;
		Font *m_font;
		ID3D11ShaderResourceView *m_fontTexture;
		Texture *m_sampler;
		
	};
}
#endif