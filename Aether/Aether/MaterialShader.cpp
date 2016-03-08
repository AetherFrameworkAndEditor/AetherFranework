#include "MaterialShader.h"
#include"ModelUtility.h"

using namespace aetherClass;
using namespace aetherFunction;
MaterialShader::MaterialShader()
{
	m_camera = nullptr;
	m_light = nullptr;
	m_lightBuffer = nullptr;
	m_cameraBuffer = nullptr;
}


MaterialShader::~MaterialShader()
{
}

bool MaterialShader::InitializeShader(){
	HRESULT result;
	result = GetDirect3DManager()->GetDevice()->CreateBuffer(&GetConstantBufferDesc(sizeof(Light)), NULL, &m_lightBuffer);
	if (FAILED(result)){
		return false;
	}
	result = GetDirect3DManager()->GetDevice()->CreateBuffer(&GetConstantBufferDesc(sizeof(CameraBuffer)), NULL, &m_cameraBuffer);
	if (FAILED(result)){
		return false;
	}

}
void MaterialShader::FinalizeShader(){
	m_lightBuffer->Release();
	m_cameraBuffer->Release();
}
bool MaterialShader::SetConstantBuffer(){
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mapped;
	Light *dataptr;
	CameraBuffer *dataptr2;
	unsigned int bufferNumber;

	result = GetDirect3DManager()->GetDeviceContext()->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	if (FAILED(result)){
		return false;
	}
	dataptr = (Light*)mapped.pData;
	*dataptr = *m_light;
	GetDirect3DManager()->GetDeviceContext()->Unmap(m_lightBuffer, 0);
	bufferNumber = 2;
	GetDirect3DManager()->GetDeviceContext()->PSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);

	result = GetDirect3DManager()->GetDeviceContext()->Map(m_cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	if (FAILED(result)){
		return false;
	}
	dataptr2 = (CameraBuffer*)mapped.pData;
	dataptr2->_Position = m_camera->property._translation;
	GetDirect3DManager()->GetDeviceContext()->Unmap(m_cameraBuffer, 0);
	bufferNumber = 1;
	GetDirect3DManager()->GetDeviceContext()->VSSetConstantBuffers(bufferNumber, 1, &m_cameraBuffer);

	return true;
}

void MaterialShader::SetLight(Light* light){
	m_light = light;
}
void MaterialShader::SetCamera(ViewCamera* camera){
	m_camera = camera;
}