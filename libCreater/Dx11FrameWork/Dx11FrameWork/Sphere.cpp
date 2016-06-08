#include "Sphere.h"
using namespace aetherClass;

Sphere::Sphere(UINT slice,UINT stack)
{
	m_radius = 1;
	m_sliceCount = slice;
	m_stackCount = stack;
	SetName("Sphere");
}


Sphere::~Sphere()
{
}

bool Sphere::InitializeBuffers(){

	VertexType* vertices = nullptr;
	unsigned long* indices = nullptr;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 256 * 256;
	m_indexCount = m_vertexCount;

	vertices = new VertexType[m_vertexCount];
	if (!vertices){
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if (!indices){
		return false;
	}

	//float radius = 10.0f;
	//UINT sliceCount = 50;
	//UINT stackCount = 50;
	int count = 1;
	std::vector<unsigned long> vindices;

	Vector3 topVertex(0.0f, +m_radius, 0.0f);
	Vector3 bottomVertex(0.0f, -m_radius, 0.0f);

	vertices[0]._position = topVertex;

	float phiStep = kAetherPI / m_stackCount;
	float thetaStep = 2.0f * kAetherPI / m_sliceCount;

	for (UINT i = 1; i <= m_stackCount - 1; ++i)
	{
		float phi = i*phiStep;

		for (UINT j = 0; j <= m_sliceCount; ++j)
		{
			float theta = j*thetaStep;

			Vector3 vec;
			vec._x = m_radius * sinf(phi)*cosf(theta);
			vec._y = m_radius * cosf(phi);
			vec._z = m_radius * sinf(phi)*sinf(theta);

			Vector2 uv;
			uv._x = theta / kAetherPI;
			uv._y = phi / kAetherPI;

			vertices[count]._position = vec;
			vertices[count]._uv = uv;

			count++;
		}
	}

	vertices[count + 1]._position = bottomVertex;

	for (UINT i = 1; i <= m_sliceCount; i++)
	{
		vindices.push_back(0);
		vindices.push_back(i + 1);
		vindices.push_back(i);
	}

	UINT baseIndex = 1;
	UINT ringVertexCount = m_sliceCount + 1;
	for (UINT i = 0; i < m_stackCount - 2; ++i)
	{
		for (UINT j = 0; j < m_sliceCount; ++j)
		{
			vindices.push_back(baseIndex + i*ringVertexCount + j);
			vindices.push_back(baseIndex + i*ringVertexCount + j + 1);
			vindices.push_back(baseIndex + (i + 1)*ringVertexCount + j);

			vindices.push_back(baseIndex + (i + 1)*ringVertexCount + j);
			vindices.push_back(baseIndex + i*ringVertexCount + j + 1);
			vindices.push_back(baseIndex + (i + 1)*ringVertexCount + j + 1);
		}
	}

	UINT southPoleIndex = (UINT)sizeof(vertices) - 1;

	baseIndex = southPoleIndex - ringVertexCount;

	for (UINT i = 0; i < m_sliceCount; ++i)
	{
		vindices.push_back(southPoleIndex);
		vindices.push_back(baseIndex + i);
		vindices.push_back(baseIndex + i + 1);
	}

	for (UINT i = 0; i < vindices.size(); ++i)
	{
		indices[i] = vindices[i];
	}

	// Set up the description of the static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType)*m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer
	result = GetDirect3DManager()->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{

		return false;
	}

	// Set up description of the static index buffer
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long)*m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer
	result = GetDirect3DManager()->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{

		return false;
	}

	// Relese the arrays now that the vertex and index buffers have been created and loaded
	delete[] vertices;
	delete[] indices;
	vindices.clear();

	return true;
}

void Sphere::FinalizeBuffers(){

}

void Sphere::RenderBuffers(){
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered
	GetDirect3DManager()->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered
	GetDirect3DManager()->GetDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer,in this case triangle
	GetDirect3DManager()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}