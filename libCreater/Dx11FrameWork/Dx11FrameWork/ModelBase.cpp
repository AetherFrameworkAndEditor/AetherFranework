#include "ModelBase.h"
#include"ModelUtility.h"
#include "Material.h"
#include <assert.h>
using namespace aetherFunction;
using namespace aetherClass;
using namespace DirectX;
ModelBase::ModelBase()
{
}
bool ModelBase::Initialize(){
	bool result;
	m_vertexBuffer = nullptr;
	m_indexBuffer = nullptr;
	m_texture = nullptr;
	m_vertexCount = 0;
	m_indexCount = 0;

	property._transform._scale = Vector3(1, 1, 1);
	// Create Basecolor constant buffers.
	GetDirect3DManager()->GetDevice()->CreateBuffer(&GetConstantBufferDesc(sizeof(Color)), NULL, &m_colorBuffer);	
	GetDirect3DManager()->GetDevice()->CreateBuffer(&GetConstantBufferDesc(sizeof(MaterialBufferType)), NULL, &m_materialBuffer);

	// Initialize the vertex and index buffers.
	result = InitializeBuffers();

	return result;
}

void ModelBase::Finalize()
{
	// ”h¶æ‚Ì‰ð•úˆ—
	FinalizeBuffers();

	if (m_materialBuffer){
		m_materialBuffer->Release();
		m_materialBuffer = nullptr;
	}
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


void ModelBase::Render(ShaderBase* shader){
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers();

	Matrix4x4 view;
	Matrix4x4 world;

	world.Identity();

	view = m_camera->GetViewMatrix();
	Matrix4x4 projection = GetDirect3DManager()->GetProjectionMatrix();

	world = property._transform.Transmatrix();
	
	CreateConstantBuffers();

	shader->Render(GetIndexCount(),world, view, projection);
	

	return;
}

//
int ModelBase::GetIndexCount(){
	return m_indexCount;
}

//
void ModelBase::SetTexture(Texture* texture){
	m_texture = texture;

	return;
}

//
void ModelBase::SetCamera(ViewCamera* camera){
	m_camera = camera;
}

//
void ModelBase::CreateConstantBuffers(){
	D3D11_MAPPED_SUBRESOURCE mapped;
	Color *dataptr;
	MaterialBufferType *dataptr2;
	unsigned int bufferNumber;

	GetDirect3DManager()->GetDeviceContext()->Map(m_colorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	dataptr = (Color*)mapped.pData;
	*dataptr = property._color;
	GetDirect3DManager()->GetDeviceContext()->Unmap(m_colorBuffer, 0);
	bufferNumber = 0;
	GetDirect3DManager()->GetDeviceContext()->PSSetConstantBuffers(bufferNumber, 1, &m_colorBuffer);
	
	bufferNumber = 1;
	GetDirect3DManager()->GetDeviceContext()->Map(m_materialBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);

	dataptr2 = (MaterialBufferType*)mapped.pData;
	dataptr2->_diffuse = property._material._diffuse._color;
	dataptr2->_specular = property._material._specular._color;
	dataptr2->_ambient = property._material._ambient._color;
	dataptr2->_emissive = property._material._emissive._color;
	dataptr2->_specularPower = property._material._specularPower;
	dataptr2->_shininess = property._material._shininess;
	dataptr2->_transparencyFactor = property._material._transparencyFactor;

	GetDirect3DManager()->GetDeviceContext()->Unmap(m_materialBuffer, 0);
	GetDirect3DManager()->GetDeviceContext()->PSSetConstantBuffers(bufferNumber, 1, &m_materialBuffer);


	if (m_texture){
		ID3D11ShaderResourceView* tex = m_texture->GetTexture();
		ID3D11SamplerState* sampler = m_texture->GetSamplerState();

		GetDirect3DManager()->GetDeviceContext()->PSSetSamplers(0, 1, &sampler);
		GetDirect3DManager()->GetDeviceContext()->PSSetShaderResources(0, 1, &tex);
	}
}

//
void ModelBase::SetName(const std::string name){
	m_modelName = name;
}

//
std::string ModelBase::GetName()const{
	return m_modelName;
}

Axis& ModelBase::GetAxis(){
	return m_axis;
}

