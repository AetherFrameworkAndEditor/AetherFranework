#include "Skybox.h"

using namespace aetherClass;
Skybox::Skybox()
{
	m_samplerState = nullptr;
	SetName("SkyBox");
}


Skybox::~Skybox()
{
}

bool Skybox::InitializeBuffers(){

	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;


	// Set the number of vertices in the vertex array.
	m_vertexCount = 24;

	// Set the number of indices in the index array.
	m_indexCount = 28;

	ZeroMemory(&vertices, sizeof(vertices));
	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	double slice_u, slice_v;

	slice_u = 1.0f / 4.0f;
	slice_v = 1.0f / 3.0f;

	//Fore
	vertices[0]._position = Vector3(1.0f, -1.0f, 1.0f);
	vertices[0]._uv = Vector2(slice_u * 3,slice_v*2);

	vertices[1]._position = Vector3(1.0f, 1.0f, 1.0f);
	vertices[1]._uv = Vector2(slice_u * 3, slice_v * 1);

	vertices[2]._position = Vector3(-1.0f, -1.0f, 1.0f);
	vertices[2]._uv = Vector2(slice_u * 2, slice_v * 2);

	vertices[3]._position = Vector3(-1.0f, 1.0f, 1.0f);
	vertices[3]._uv = Vector2(slice_u * 2, slice_v * 1);


	for (int i = 0; i < 4; i++){
		vertices[i]._normal = Vector3(0, 0, 1);
	}


	//Side left
	vertices[4]._position = Vector3(-1.0f, -1.0f, 1.0f);
	vertices[4]._uv = Vector2(slice_u * 2, slice_v * 2);

	vertices[5]._position = Vector3(-1.0f, 1.0f, 1.0f);
	vertices[5]._uv = Vector2(slice_u * 2, slice_v * 1);

	vertices[6]._position = Vector3(-1.0f, -1.0f, -1.0f);
	vertices[6]._uv = Vector2(slice_u * 1, slice_v * 2);

	vertices[7]._position = Vector3(-1.0f, 1.0f, -1.0f);
	vertices[7]._uv = Vector2(slice_u * 1, slice_v * 1);

	for (int i = 0; i < 4; i++){
		vertices[i + 4]._normal = Vector3(1, 0, 0);
	}

	//Back
	vertices[8]._position = Vector3(-1.0f, -1.0f, -1.0f);
	vertices[8]._uv = Vector2(slice_u * 1, slice_v * 2);

	vertices[9]._position = Vector3(-1.0f, 1.0f, -1.0f);
	vertices[9]._uv = Vector2(slice_u * 1, slice_v * 1);

	vertices[10]._position = Vector3(1.0f, -1.0f, -1.0f);
	vertices[10]._uv = Vector2(slice_u * 0, slice_v * 2);

	vertices[11]._position = Vector3(1.0f, 1.0f, -1.0f);
	vertices[11]._uv = Vector2(slice_u * 0, slice_v * 1);

	for (int i = 0; i < 4; i++){
		vertices[i + 8]._normal = Vector3(0, 0, -1);
	}

	//Side right
	vertices[12]._position = Vector3(1.0f, -1.0f, -1.0f);
	vertices[12]._uv = Vector2(1.0, slice_v * 2 );

	vertices[13]._position = Vector3(1.0f, 1.0f, -1.0f);
	vertices[13]._uv = Vector2(1.0, slice_v * 1);

	vertices[14]._position = Vector3(1.0f, -1.0f, 1.0f);
	vertices[14]._uv = Vector2(slice_u * 3, slice_v * 2);

	vertices[15]._position = Vector3(1.0f, 1.0f, 1.0f);
	vertices[15]._uv = Vector2(slice_u * 3, slice_v * 1);

	for (int i = 0; i < 4; i++){
		vertices[i + 12]._normal = Vector3(-1, 0, 0);
	}

	//UP
	vertices[18]._position = Vector3(-1.0f, 1.0f, 1.0f);
	vertices[18]._uv = Vector2(slice_u * 2, slice_v * 1);

	vertices[19]._position = Vector3(-1.0f, 1.0f, -1.0f);
	vertices[19]._uv = Vector2(slice_u * 1, slice_v * 1);

	vertices[16]._position = Vector3(1.0f, 1.0f, 1.0f);
	vertices[16]._uv = Vector2(slice_u * 2, slice_v * 0);

	vertices[17]._position = Vector3(1.0f, 1.0f, -1.0f);
	vertices[17]._uv = Vector2(slice_u * 1, slice_v * 0);
	for (int i = 0; i < 4; i++){
		vertices[i + 16]._normal = Vector3(0, -1, 0);
	}

	//DOWN
	vertices[20]._position = Vector3(-1.0f, -1.0f, 1.0f);
	vertices[20]._uv = Vector2(slice_u * 2, slice_v * 2);

	vertices[21]._position = Vector3(-1.0f, -1.0f, -1.0f);
	vertices[21]._uv = Vector2(slice_u * 1, slice_v * 2);

	vertices[22]._position = Vector3(1.0f, -1.0f, 1.0f);
	vertices[22]._uv = Vector2(slice_u * 2, 1.0f);

	vertices[23]._position = Vector3(1.0f, -1.0f, -1.0f);
	vertices[23]._uv = Vector2(slice_u * 1, 1.0f);
	for (int i = 0; i < 4; i++){
		vertices[i + 20]._normal = Vector3(0, 1, 0);
	}


	// Load the index array with data.
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	indices[4] = 4;
	indices[5] = 5;
	indices[6] = 6;
	indices[7] = 7;

	indices[8] = 8;
	indices[9] = 9;
	indices[10] = 10;
	indices[11] = 11;

	indices[12] = 12;
	indices[13] = 13;
	indices[14] = 14;
	indices[15] = 15;

	indices[16] = 15;
	indices[17] = 16;
	indices[18] = 16;
	indices[19] = 17;
	indices[20] = 18;
	indices[21] = 19;
	indices[22] = 19;
	indices[23] = 20;
	indices[24] = 20;
	indices[25] = 21;
	indices[26] = 22;
	indices[27] = 23;




	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = GetDirect3DManager()->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = GetDirect3DManager()->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
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

	return true;

}

void Skybox::FinalizeBuffers(){
	if (m_samplerState){
		m_samplerState->Release();
		m_samplerState = nullptr;
	}
}

void Skybox::RenderBuffers(){
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset
	stride = sizeof(VertexType);
	offset = 0;

	property._transform._translation = m_camera->property._translation;
	property._transform._scale = GetDirect3DManager()->GetScreenDepth()/2;
	
	// Set the vertex buffer to active in the input assembler so it can be rendered
	GetDirect3DManager()->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered
	GetDirect3DManager()->GetDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer,in this case triangle
	GetDirect3DManager()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void Skybox::CreateConstantBuffers(){
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


	if (m_texture){
		ID3D11ShaderResourceView* tex = m_texture->GetTexture();
		ID3D11SamplerState* sampler = m_samplerState;

		GetDirect3DManager()->GetDeviceContext()->PSSetSamplers(0, 1, &sampler);
		GetDirect3DManager()->GetDeviceContext()->PSSetShaderResources(0, 1, &tex);
	}
}