/******************************************************************************/
/*! @addtogroup aetherClass
@file      Circle.cpp
@brief     ‰~‚ÌŠî–{ƒ‚ƒfƒ‹

*******************************************************************************
@date       2016/1/9 19:23
@author     ‹àŽq˜aŽ÷
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/1/9 19:23 ‹àŽq˜aŽ÷
-# Initial Version

******************************************************************************/
#include "Circle.h"
#include"MathUtility.h"

using namespace aetherClass;
Circle::Circle()
{
	m_slice = 20;
	SetName("Circle");
}


Circle::~Circle()
{
}

Circle::Circle(float slice){
	m_slice = slice;
}

bool Circle::InitializeBuffers(){

	VertexType* vertices = nullptr;
	unsigned long* indices = nullptr;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	if (m_slice < 3){
		m_slice = 3;
	}
	m_vertexCount = m_slice + 1;
	m_indexCount = m_slice * 2;


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
	
	vertices[0]._position = Vector3(0.0f, 0.0f, 0.0f);
	vertices[0]._uv = Vector2(0.5f, 0.5f);

	float x, y;
	int i = 1;
	float onceRadian = 360 / m_slice;
	for (float rad = 0; rad < 360; rad += onceRadian){
		x = sin(kAetherPI*rad / 180);
		y = cos(kAetherPI*rad / 180);
		vertices[i]._position = Vector3(x, y, 0);
		vertices[i]._uv = Vector2(0.5 + (x*0.5), 0.5 + (y*0.5));
		i++;
	}

	int cr = 0;
	for (int i = 1; i < m_vertexCount; ++i){
		indices[cr++] = i;
		indices[cr++] = 0;
	}
	indices[--cr] = 1;

	for (int f = 0; f < m_vertexCount; ++f){
		vertices[f]._normal = Vector3(0.0f, 0.0f, -1.0f);
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
	return true;
}

void Circle::FinalizeBuffers(){

}

void Circle::RenderBuffers(){
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