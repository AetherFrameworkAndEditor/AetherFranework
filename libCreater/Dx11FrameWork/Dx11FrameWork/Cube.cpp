#include "Cube.h"

using namespace aetherClass;
Cube::Cube()
{
}


Cube::~Cube()
{
}

bool Cube::InitializeBuffers(){

	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;


	m_vertexCount = 24;
	m_indexCount = 28;

	ZeroMemory(&vertices, sizeof(vertices));
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}


	//Fore
	vertices[0]._position = Vector3(1.0f, -1.0f, -1.0f);
	vertices[0]._uv = Vector2(1.0f, 1.0f);

	vertices[1]._position = Vector3(1.0f, 1.0f, -1.0f);
	vertices[1]._uv = Vector2(1.0f, 0.0f);

	vertices[2]._position = Vector3(-1.0f, -1.0f, -1.0f);
	vertices[2]._uv = Vector2(0.0f, 1.0f);

	vertices[3]._position = Vector3(-1.0f, 1.0f, -1.0f);
	vertices[3]._uv = Vector2(0.0f, 0.0f);


	for (int i = 0; i < 4; i++){
		vertices[i]._normal = Vector3(0, 0, -1);
	}


	//Side left
	vertices[4]._uv = Vector2(1.0f, 1.0f);
	vertices[4]._position = Vector3(-1.0f, -1.0f, -1.0f);

	vertices[5]._position = Vector3(-1.0f, 1.0f, -1.0f);
	vertices[5]._uv = Vector2(1.0f, 0.0f);

	vertices[6]._position = Vector3(-1.0f, -1.0f, 1.0f);
	vertices[6]._uv = Vector2(0.0f, 1.0f);

	vertices[7]._position = Vector3(-1.0f, 1.0f, 1.0f);
	vertices[7]._uv = Vector2(0.0f, 0.0f);

	for (int i = 0; i < 4; i++){
		vertices[i + 4]._normal = Vector3(-1, 0, 0);
	}

	//Back
	vertices[8]._position = Vector3(-1.0f, -1.0f, 1.0f);
	vertices[8]._uv = Vector2(1.0f, 1.0f);

	vertices[9]._position = Vector3(-1.0f, 1.0f, 1.0f);
	vertices[9]._uv = Vector2(1.0f, 0.0f);

	vertices[10]._position = Vector3(1.0f, -1.0f, 1.0f);
	vertices[10]._uv = Vector2(0.0f, 1.0f);

	vertices[11]._position = Vector3(1.0f, 1.0f, 1.0f);
	vertices[11]._uv = Vector2(0.0f, 0.0f);

	for (int i = 0; i < 4; i++){
		vertices[i + 8]._normal = Vector3(0, 0, 1);
	}

	//Side right
	vertices[12]._position = Vector3(1.0f, -1.0f, 1.0f);
	vertices[12]._uv = Vector2(1.0f, 1.0f);

	vertices[13]._position = Vector3(1.0f, 1.0f, 1.0f);
	vertices[13]._uv = Vector2(1.0f, 0.0f);

	vertices[14]._position = Vector3(1.0f, -1.0f, -1.0f);
	vertices[14]._uv = Vector2(0.0f, 1.0f);

	vertices[15]._position = Vector3(1.0f, 1.0f, -1.0f);
	vertices[15]._uv = Vector2(0.0f, 0.0f);

	for (int i = 0; i < 4; i++){
		vertices[i + 12]._normal = Vector3(1, 0, 0);
	}

	//UP
	vertices[18]._position = Vector3(-1.0f, 1.0f, -1.0f);
	vertices[18]._uv = Vector2(0.0f, 1.0f);

	vertices[19]._position = Vector3(-1.0f, 1.0f, 1.0f);
	vertices[19]._uv = Vector2(0.0f, 0.0f);

	vertices[16]._position = Vector3(1.0f, 1.0f, -1.0f);
	vertices[16]._uv = Vector2(1.0f, 1.0f);

	vertices[17]._position = Vector3(1.0f, 1.0f, 1.0f);
	vertices[17]._uv = Vector2(1.0f, 0.0f);
	for (int i = 0; i < 4; i++){
		vertices[i + 16]._normal = Vector3(0, 1, 0);
	}

	//DOWN
	vertices[20]._position = Vector3(-1.0f, -1.0f, -1.0f);
	vertices[20]._uv = Vector2(0.0f, 1.0f);

	vertices[21]._position = Vector3(-1.0f, -1.0f, 1.0f);
	vertices[21]._uv = Vector2(0.0f, 0.0f);

	vertices[22]._position = Vector3(1.0f, -1.0f, -1.0f);
	vertices[22]._uv = Vector2(1.0f, 1.0f);

	vertices[23]._position = Vector3(1.0f, -1.0f, 1.0f);
	vertices[23]._uv = Vector2(1.0f, 0.0f);
	for (int i = 0; i < 4; i++){
		vertices[i + 20]._normal = Vector3(0, -1, 0);
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




	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = GetDirect3DManager()->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = GetDirect3DManager()->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;

}

void Cube::FinalizeBuffers(){

}

void Cube::RenderBuffers(){
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	GetDirect3DManager()->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	GetDirect3DManager()->GetDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	GetDirect3DManager()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}
