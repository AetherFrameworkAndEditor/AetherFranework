#include "Line.h"
using namespace aetherClass;
Line::Line()
{
	m_rayVector._direction = Vector3(0.0f, 1.0f, 0.0f);
	m_rayVector._scaler = 1;
	SetName("Line");
}


Line::~Line()
{
}

Line::Line(RayVector input){
	m_rayVector = input;
}
Line::Line(Vector3 direction, float scaler){
	m_rayVector._direction= direction;
	m_rayVector._scaler= scaler;
}



bool Line::InitializeBuffers(){

	VertexType* vertices = nullptr;
	unsigned long* indices = nullptr;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 2;
	m_indexCount = 2;

	vertices = new VertexType[m_vertexCount];
	if (!vertices){
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if (!indices){
		return false;
	}
	ZeroMemory(vertices, sizeof(vertices));
	ZeroMemory(indices, sizeof(indices));


	// Load the vertex array with data.
	vertices[0]._position = Vector3(0.0f,0.0f,0.0f);
	vertices[0]._uv = Vector2(0.0f, 1.0f);

	vertices[1]._position = m_rayVector._direction*m_rayVector._scaler;
	vertices[1]._uv = Vector2(0.0f, 0.0f);


	indices[0] = 0;
	indices[1] = 1;

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
	return true;
}

void Line::FinalizeBuffers(){

}

void Line::RenderBuffers(){
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
	GetDirect3DManager()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
}