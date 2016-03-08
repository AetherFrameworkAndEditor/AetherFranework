/******************************************************************************/
/*! @addtogroup aetherClass
@file      Rectangle3D.cpp
@brief     ŽlŠpŒ`‚ÌŠî–{ƒ‚ƒfƒ‹

*******************************************************************************
@date       2016/1/12 19:23
@author     ‹àŽq˜aŽ÷
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/1/12 19:23 ‹àŽq˜aŽ÷
-# Initial Version

******************************************************************************/
#include "Rectangle3D.h"
using namespace aetherClass;

Rectangle3D::Rectangle3D()
{
	SetName("Rectangle3D");
}


Rectangle3D::~Rectangle3D()
{
}

bool Rectangle3D::InitializeBuffers(){
	VertexType* vertices = nullptr;
	unsigned long* indices = nullptr;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 4;

	vertices = new VertexType[m_vertexCount];
	if (!vertices){
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if (!indices){
		return false;
	}

	// Load the vertex array with data.
	//Fore
	vertices[0]._position = Vector3(1.0f, -1.0f, 0.0f);
	vertices[0]._uv = Vector2(1.0f, 1.0f);
	vertices[0]._normal = Vector3(0.0f, 0.0f, -1.0f);

	vertices[1]._position = Vector3(1.0f, 1.0f, 0.0f);
	vertices[1]._uv = Vector2(1.0f, 0.0f);
	vertices[1]._normal = Vector3(0.0f, 0.0f, -1.0f);

	vertices[2]._position = Vector3(-1.0f, -1.0f, 0.0f);
	vertices[2]._uv = Vector2(0.0f, 1.0f);
	vertices[2]._normal = Vector3(0.0f, 0.0f, -1.0f);

	vertices[3]._position = Vector3(-1.0f, 1.0f, 0.0f);
	vertices[3]._uv = Vector2(0.0f, 0.0f);
	vertices[3]._normal = Vector3(0.0f, 0.0f, -1.0f);

	


	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;	//top right

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	vertexBufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	vertexBufferDesc.StructureByteStride = sizeof(VertexType);

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
		assert(!"aaaaaaaaaaaaaaaaaaaaa");

		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;


	return true;
}

void Rectangle3D::FinalizeBuffers(){

}

#include<iostream>
void Rectangle3D::VertexData(){
	D3D11_MAPPED_SUBRESOURCE pMap;
	HRESULT hResult;

	hResult = GetDirect3DManager()->GetDeviceContext()->Map(m_vertexBuffer, 0, D3D11_MAP_READ, 0, &pMap);
	if (FAILED(hResult)){
		assert(!"EXPR");
	}
	VertexType* pBits = (VertexType*)pMap.pData;
	vertex = pBits;

	GetDirect3DManager()->GetDeviceContext()->Unmap(m_vertexBuffer, 0);
	ReadVertexData();
}

void Rectangle3D::ReadVertexData(){
	VertexType *ptr = vertex;

	for (int i = 0; i < m_vertexCount; i++){
		printf("%d x %.2f\n", i, ptr->_position._x);
		printf("%d y %.2f\n", i, ptr->_position._y);
		printf("%d z %.2f\n\n", i, ptr->_position._z);
		ptr++;
	}
	

}

void Rectangle3D::RenderBuffers(){
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