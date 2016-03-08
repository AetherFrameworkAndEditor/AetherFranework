#include "Font.h"

using namespace aetherClass;
Font::Font()
{
	m_hFont = NULL;
}


Font::~Font()
{
	Release();
}


bool Font::Load(FontDesc& desc){
	m_fontDesc = desc;

	DESIGNVECTOR design;
	
	if (m_hFont){
		RemoveFontResourceEx(m_fontDesc._fileName.c_str(), FR_PRIVATE, &design);
		DeleteObject(m_hFont);
		m_hFont = NULL;
	}
	AddFontResourceEx(desc._fileName.c_str(), FR_PRIVATE, &design);	

	m_hFont = CreateFont(desc._fontSize, desc._width, desc._escapement, desc._orientation, desc._fontThick, desc._itatic, desc._underLine,
		desc._strikeOut, desc._charSet, desc._outputPrecision, desc._clipPrecision, desc._quality,desc._pitchAndFamily, desc._fontName.c_str());
	if (!(m_hFont)){
		_ASSERT_EXPR(false,"Could not create Fonts");
		return false;
	}

	return true;
}

void Font::Release(){
	if (m_hFont){
		DESIGNVECTOR design;
		RemoveFontResourceEx(m_fontDesc._fileName.c_str(), FR_PRIVATE, &design);
		DeleteObject(m_hFont);
		m_hFont = NULL;
	}
}


HFONT Font::GetFont(){
	return m_hFont;
}