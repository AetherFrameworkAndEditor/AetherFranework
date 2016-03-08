#include "LightShader.h"

using namespace aetherClass;
using namespace aetherFunction;
LightShader::LightShader()
{
	m_light = nullptr;
	m_lightBuffer = nullptr;
}


LightShader::~LightShader()
{
}

bool LightShader::InitializeShader(){
	HRESULT result;
	result = GetDirect3DManager()->GetDevice()->CreateBuffer(&GetConstantBufferDesc(sizeof(Light)),NULL,&m_lightBuffer);
	if (FAILED(result)){
		return false;
	}

	return true;
}
void LightShader::FinalizeShader(){
	m_lightBuffer->Release();
}
bool LightShader::SetConstantBuffer(){
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mapped;
	Light *dataptr;
	unsigned int bufferNumber;

	result = GetDirect3DManager()->GetDeviceContext()->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	if (FAILED(result)){
		return false;
	}
	dataptr = (Light*)mapped.pData;
	*dataptr = *m_light;
	GetDirect3DManager()->GetDeviceContext()->Unmap(m_lightBuffer, 0);
	bufferNumber = 1;
	GetDirect3DManager()->GetDeviceContext()->VSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);

	return true;
}

void LightShader::SetLight(Light* light){
	m_light = light;
}