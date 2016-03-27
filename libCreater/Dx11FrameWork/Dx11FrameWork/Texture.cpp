#include "Texture.h"
#include <D3DX11tex.h>
using namespace aetherClass;

Texture::Texture()
{
	m_texture = nullptr;
	m_texture = nullptr;

}

Texture::~Texture()
{
	Release();
}

//
bool Texture::Load(std::string filename){

	HRESULT result;

	// Load the texture
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = GetDirect3DManager()->GetDevice()->CreateSamplerState(&samplerDesc, &m_samplerState);
	if (FAILED(result)){
		return false;
	}
	
	D3DX11CreateShaderResourceViewFromFileA(GetDirect3DManager()->GetDevice(), filename.c_str(), NULL, NULL, &m_texture, &result);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

//
void Texture::Release(){
	// Release the vertex texture resource
	if (m_texture)
	{
		m_texture->Release();
		m_texture = nullptr;
	}

	if (m_samplerState)
	{
		m_samplerState->Release();
		m_samplerState = nullptr;
	}
	return;
}

//
ID3D11ShaderResourceView* Texture::GetTexture(){
	return m_texture;
}

//
ID3D11SamplerState* Texture::GetSamplerState(){
	return m_samplerState;
}

//
std::string Texture::GetPath()const{
	return m_path;
}