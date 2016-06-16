#include "Mesh.h"

using namespace aetherClass;
Mesh::Mesh()
{
	_animationCount = NULL;
}


Mesh::~Mesh()
{
}

//
ID3D11ShaderResourceView* Mesh::GetTexture(){
	return  _texture->GetTexture();
}

//
ID3D11SamplerState* Mesh::GetSamplerState(){
	return _texture->GetSamplerState();
}

//
void Mesh::SetTexture(Texture* texture){
	_texture = texture;
}
bool Mesh::IsTextureVisible(){
	if (!_texture)
	{
		return false;
	}
	return true;
}
//
void Mesh::Release(){
	this->ReleaseBuffer();
	this->ResetProperty();
}

//
void Mesh::ReleaseBuffer(){

	if (_materialBuffer)
	{
		_materialBuffer->Release();
		_materialBuffer = nullptr;
	}


	if (_colorBuffer)
	{
		_colorBuffer->Release();
		_colorBuffer = nullptr;
	}

	if (_vertexBuffer)
	{
		_vertexBuffer->Release();
		_vertexBuffer = nullptr;
	}

	if (_indexBuffer)
	{
		_indexBuffer->Release();
		_indexBuffer = nullptr;
	}
}

//
void Mesh::ResetProperty(){

	_vertexBuffer = nullptr;
	_indexBuffer = nullptr;
	_colorBuffer = nullptr;
	_texture = nullptr;
	SecureZeroMemory(&_meshMatrix, sizeof(_meshMatrix));
	this->property._transform._scale = 1.0f;
	this->property._color = Color(0.9f, 0.0f, 0.9f, 1.0f);
	_vertexCount = _indexCount = NULL;
}

