#include "SpriteBase.h"
#include"ModelUtility.h"
#include "Material.h"
#include <assert.h>

using namespace aetherClass;
using namespace aetherFunction;
using namespace DirectX;

SpriteBase::SpriteBase()
{
}


bool SpriteBase::Initialize(){
	bool result;
	m_vertexBuffer = nullptr;
	m_indexBuffer = nullptr;
	m_texture = nullptr;
	m_vertexCount = 0;
	m_indexCount = 0;

	property._transform._scale = Vector3(1, 1, 1);
	// Create Basecolor constant buffers.
	GetDirect3DManager()->GetDevice()->CreateBuffer(&GetConstantBufferDesc(sizeof(Color)), NULL, &m_colorBuffer);

	// Initialize the vertex and index buffers.
	result = InitializeBuffers();

	return result;
}

void SpriteBase::Finalize()
{
	// ”h¶æ‚Ì‰ð•úˆ—
	FinalizeBuffers();

	if (m_colorBuffer){
		m_colorBuffer->Release();
		m_colorBuffer = nullptr;
	}
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = nullptr;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = nullptr;
	}

	m_vertexCount = 0;
	m_indexCount = 0;
	return;
}


void SpriteBase::Render(ShaderBase* shader){
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers();

	Matrix4x4 view;
	Matrix4x4 world;


	world.Identity();
	view.Identity();

	Matrix4x4 projection = GetDirect3DManager()->GetOrthoMatrix();
	projection._22 *= -1;
	projection._33 = 1; projection._34 = 0;
	projection._41 = -1, projection._42 = 1, projection._43 = 0, projection._44 = 1;


	world = property._transform.Transmatrix();
	CreateConstantBuffers();

	shader->Render(GetIndexCount(), world, view, projection);

	return;
}

int SpriteBase::GetIndexCount(){
	return m_indexCount;
}

void SpriteBase::SetTexture(Texture* texture){
	m_texture = texture;

	return;
}


void SpriteBase::CreateConstantBuffers(){
	D3D11_MAPPED_SUBRESOURCE mapped;
	Color *dataptr;
	unsigned int bufferNumber;

	GetDirect3DManager()->GetDeviceContext()->Map(m_colorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	dataptr = (Color*)mapped.pData;
	*dataptr = property._color;
	GetDirect3DManager()->GetDeviceContext()->Unmap(m_colorBuffer, 0);
	bufferNumber = 0;
	GetDirect3DManager()->GetDeviceContext()->PSSetConstantBuffers(bufferNumber, 1, &m_colorBuffer);


	if (m_texture){
		ID3D11ShaderResourceView* tex = m_texture->GetTexture();
		ID3D11SamplerState* sampler = m_texture->GetSamplerState();

		GetDirect3DManager()->GetDeviceContext()->PSSetSamplers(0, 1, &sampler);
		GetDirect3DManager()->GetDeviceContext()->PSSetShaderResources(0, 1, &tex);
	}
}

std::string SpriteBase::GetName(){
	return m_spriteName;
}


void SpriteBase::SetName(std::string name){
	m_spriteName = name;
}