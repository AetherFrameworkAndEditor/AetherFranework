#include "Text.h"
#include<vector>
#include<iostream>
using namespace aetherClass;
Text::Text()
{
	m_font = nullptr;
	m_fontTexture = nullptr;
	m_texture = nullptr;
	m_sampler = new Texture();
	m_sampler->Load("");
	SetName("Text");
}


Text::~Text()
{
	m_fontTexture->Release();
	delete m_sampler;
}

void Text::SetFont(Font *font){
	m_font = font;
}

BYTE* GetData(GLYPHMETRICS &GM,UINT& code,HDC &hdc){
	CONST MAT2 Mat = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
	DWORD size = 0;
	SecureZeroMemory(&GM, sizeof(GM));
	size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);

	BYTE* ptr = new BYTE[size];
	GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);
	return ptr;
}

bool Text::UpdateText(std::wstring str){
	HRESULT hResult;

	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, m_font->GetFont());
	UINT code = 0;


	ID3D11Texture2D **stringTextureList = new ID3D11Texture2D*[str.length()];
	unsigned int *charWidth = new unsigned int[str.length()];
	UINT texWidth = 0;

	TEXTMETRIC TM;
	GetTextMetrics(hdc, &TM);
	GLYPHMETRICS GM;


	for (int i = 0; i < str.length(); i++){
	code = (UINT)*(str.begin() + i);
	BYTE* ptr = GetData(GM, code, hdc);

	/*printf("blackboxX %d,blackboxY %d\n", GM.gmBlackBoxX, GM.gmBlackBoxY);
	printf("cellIncX %d,cellIncY %d\n", GM.gmCellIncX, GM.gmCellIncY);
	printf("GlyphOrigin%d\n", GM.gmptGlyphOrigin);*/


	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Width = GM.gmCellIncX;
	desc.Height = TM.tmHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// RGBA(255,255,255,255)タイプ
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DYNAMIC;			// 動的（書き込みするための必須条件）
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// シェーダリソースとして使う
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPUからアクセスして書き込みOK

	ID3D11Texture2D	*tex2D;					///< 2Ｄテクスチャ
	hResult = GetDirect3DManager()->GetDevice()->CreateTexture2D(&desc, 0, &tex2D);
	if (FAILED(hResult)){
		_ASSERT_EXPR(false, L"Could not Create Texture");
	}
	
	D3D11_MAPPED_SUBRESOURCE hMappedResource;
	hResult = GetDirect3DManager()->GetDeviceContext()->Map(
		tex2D,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&hMappedResource);

	// ここで書き込む
	BYTE* pBits = (BYTE*)hMappedResource.pData;

	// フォント情報の書き込み
	// iOfs_x, iOfs_y : 書き出し位置(左上)
	// iBmp_w, iBmp_h : フォントビットマップの幅高
	// Level : α値の段階 (GGO_GRAY4_BITMAPなので17段階)
	int iOfs_x = GM.gmptGlyphOrigin.x;
	int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
	int iBmp_w = GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4;
	int iBmp_h = GM.gmBlackBoxY;
	int Level = 17;
	int x, y;
	DWORD Alpha, Color;
	memset(pBits, 0, hMappedResource.RowPitch * TM.tmHeight);
	for (y = iOfs_y; y < iOfs_y + iBmp_h; y++)
	{
		for (x = iOfs_x; x < iOfs_x + iBmp_w; x++)
		{	

			Alpha = (255 * ptr[x - iOfs_x + iBmp_w * (y - iOfs_y)]) / (Level - 1);
			Color = 0x00000000 | (Alpha << 24);

			memcpy((BYTE*)pBits + hMappedResource.RowPitch * y + 4 * x, &Color, sizeof(DWORD));
		}
	}
	texWidth +=	charWidth[i] = x;


	/*printf("char %c %d\n", code, code);
		printf("char%d\n", charWidth[i]);

	printf("Buffer?size %d\n",size);
	printf("x %d origin x %d\n", x,iOfs_x);
	printf("y %d origin y %d\n", y, iOfs_y);
	printf("%d\n", iBmp_w);
	printf("%d\n", iBmp_h);

	printf("Wid %d,Hei %d\n", GM.gmCellIncX, TM.tmHeight);
	printf("OriginTex Row	\t%d\n", hMappedResource.RowPitch);
	printf("OriginTex Depth	\t%d\n\n", hMappedResource.DepthPitch);*/



	GetDirect3DManager()->GetDeviceContext()->Unmap(tex2D, 0);


	stringTextureList[i] = tex2D;
	//tex2D->Release();
	delete[] ptr;

	}
	property._transform._scale._x = texWidth; // テクスチャの横幅
	property._transform._scale._y = TM.tmHeight; // テクスチャの高さ

	//フォント元に戻す作業
	SelectObject(hdc, oldFont);
	ReleaseDC(NULL, hdc);
	
	//テクスチャ結合予定
	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Width = texWidth;
	desc.Height = TM.tmHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// RGBA(255,255,255,255)タイプ
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DYNAMIC;			// 動的（書き込みするための必須条件）
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// シェーダリソースとして使う
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// CPUからアクセスして書き込みOK

	ID3D11Texture2D *stringTexture;
	hResult = GetDirect3DManager()->GetDevice()->CreateTexture2D(&desc, 0, &stringTexture);
	if (FAILED(hResult)){
		_ASSERT_EXPR(false, L"Could not Create Texture");
	}

	D3D11_MAPPED_SUBRESOURCE hMappedResource;
	hResult = GetDirect3DManager()->GetDeviceContext()->Map(
		stringTexture,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&hMappedResource);

	// ここで書き込む
	BYTE* pTex = (BYTE*)hMappedResource.pData;

	/*
	printf("%d,%d\n", texWidth, TM.tmHeight);

	printf("AppendTex Row	\t%d\n", hMappedResource.RowPitch);
	printf("AppendTex Depth	\t%d\n", hMappedResource.DepthPitch);
	*/


	UINT nextPos = 0;
	for (int i = 0; i < str.length(); i++){
		D3D11_MAPPED_SUBRESOURCE hMappedResource2;
		hResult = GetDirect3DManager()->GetDeviceContext()->Map(
			stringTextureList[i],
			0,
			D3D11_MAP_WRITE_DISCARD,
			0,
			&hMappedResource2);

			/*printf("\nsrcTex Row	%d",hMappedResource2.RowPitch);
			printf("\nsrcTex Depth	%d\n", hMappedResource2.DepthPitch);*/
		for (int y = 0; y < TM.tmHeight; y++){
				/*printf("x %d y %d\n", i, y);
				printf("AppendColumn\t%d AppendRow\t%d\n", y*hMappedResource.RowPitch, i*hMappedResource2.RowPitch);
				printf("nowAppend\t%d\n", (i*hMappedResource2.RowPitch) + (y*hMappedResource.RowPitch));
				printf("SrcRow\t%d\n", hMappedResource2.RowPitch*(y+1));*/
				memcpy(pTex +(nextPos) + (y*hMappedResource.RowPitch),
					(BYTE*)hMappedResource2.pData+(y*hMappedResource2.RowPitch),
					charWidth[i]*4);
		}
		nextPos += charWidth[i]*4;

		GetDirect3DManager()->GetDeviceContext()->Unmap(stringTextureList[i], 0);
	}

	GetDirect3DManager()->GetDeviceContext()->Unmap(stringTexture, 0);


	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;


	//std::cout <<std::endl<< &stringTextureList[0]<<"\n"<<&stringTextureList[1];



	/**/
	if (m_fontTexture){
		m_fontTexture->Release();
	}
	hResult = GetDirect3DManager()->GetDevice()->CreateShaderResourceView(stringTexture, &srvDesc, &m_fontTexture);


	for (int i = 0; i < str.length(); i++){
		stringTextureList[i]->Release();
	}
	stringTexture->Release();
	delete[] charWidth;

	return true;
}

void Text::CreateConstantBuffers(){
	D3D11_MAPPED_SUBRESOURCE mapped;
	Color *dataptr;
	unsigned int bufferNumber;

	bufferNumber = 0;
	GetDirect3DManager()->GetDeviceContext()->Map(m_colorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);

	dataptr = (Color*)mapped.pData;
	*dataptr = property._color;

	GetDirect3DManager()->GetDeviceContext()->Unmap(m_colorBuffer, 0);
	GetDirect3DManager()->GetDeviceContext()->PSSetConstantBuffers(bufferNumber, 1, &m_colorBuffer);


	ID3D11ShaderResourceView* tex;
	if (m_fontTexture){
		tex = m_fontTexture;
	}/*if(m_texture){
		tex[1] = m_texture->GetTexture();
	}*/
	ID3D11SamplerState* sampler = m_sampler->GetSamplerState();
	GetDirect3DManager()->GetDeviceContext()->PSSetSamplers(0, 1, &sampler);
	GetDirect3DManager()->GetDeviceContext()->PSSetShaderResources(0, 1, &tex);

}