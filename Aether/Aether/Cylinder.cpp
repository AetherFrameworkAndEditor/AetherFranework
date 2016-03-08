/******************************************************************************/
/*! @addtogroup aetherClass
@file      Cylinder.cpp
@brief     円柱の基本モデル

*******************************************************************************
@date       2016/1/9 19:23
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/1/9 19:23 金子和樹
-# Initial Version

******************************************************************************/
#include "Cylinder.h"
#include"MathUtility.h"

using namespace aetherClass;
Cylinder::Cylinder()
{
	SetName("Cylinder");
	m_slice = 20;
}


Cylinder::~Cylinder()
{
}

Cylinder::Cylinder(float slice){
	m_slice = slice;
}

bool Cylinder::InitializeBuffers(){

	VertexType* vertices = nullptr;
	unsigned long* indices = nullptr;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	if (m_slice < 3){
		m_slice = 3;
	}
	m_vertexCount = ((m_slice + 1) * 2) + (m_slice * 4);
	m_indexCount = (m_slice * 4 + 8) + (m_slice * 4);


	vertices = new  VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	float downpoly_uvCenter = 1.0 / 4;
	float x, z;
	int cr = 0, vertex = 0;
	int indexoffset = m_slice + 1;



	vertices[vertex]._position = Vector3(0.0f, 1.0f, 0.0f);
	vertices[vertex]._uv = Vector2(downpoly_uvCenter, downpoly_uvCenter);
	vertices[vertex]._normal = Vector3(0, 1, 0);

	vertices[vertex + indexoffset]._position = Vector3(0.0f, -1.0f, 0.0f);
	vertices[vertex + indexoffset]._uv = Vector2(downpoly_uvCenter, downpoly_uvCenter);
	vertices[vertex + indexoffset]._normal = Vector3(0, -1, 0);

	++vertex;
	{
		float onceRadian = 360 / m_slice;
		for (float rad = 0; rad < 360; rad += onceRadian){
			x = sin(kAetherPI*rad / 180);
			z = cos(kAetherPI*rad / 180);

			//上
			vertices[vertex]._position = Vector3(x, 1, z);
			vertices[vertex]._uv = Vector2(downpoly_uvCenter + (x*downpoly_uvCenter), downpoly_uvCenter + (z*downpoly_uvCenter));
			vertices[vertex]._normal = Vector3(0, 1, 0);


			//底
			vertices[vertex + indexoffset]._position = Vector3(x, -1, z);
			vertices[vertex + indexoffset]._uv = Vector2(downpoly_uvCenter + (x*downpoly_uvCenter), downpoly_uvCenter + (z*downpoly_uvCenter));
			vertices[vertex + indexoffset]._normal = Vector3(0, -1, 0);

			++vertex;
		}

		for (int i = 1; i < m_slice + 1; ++i){
			indices[cr++] = i;
			indices[cr++] = 0;
		}
		indices[cr++] = 1;
		indices[cr++] = 1;
		indices[cr++] = vertex;
		indices[cr++] = vertex;

		for (int i = m_slice; i > 0; --i){
			indices[cr++] = i + indexoffset;
			indices[cr++] = indexoffset;

		}
		indices[cr++] = indexoffset + m_slice;
		indices[cr++] = indexoffset + m_slice;
		indices[cr++] = indexoffset + 1;
		indices[cr++] = indexoffset + 1;

	}//上面と底面の定義ここまで～～↓こっから壁つくるよ！！
	int preservedVertex = vertex += indexoffset;


	float uv_x = 0, uv_y = 0.5;
	float uv_w = 0, uv_h = 1.0;

	for (int rad = 1, i = 1; rad < m_slice; ++rad, ++i ){

		vertices[vertex + 1]._position = vertices[i]._position;
		vertices[vertex + 3]._position = vertices[i + 1]._position;

		uv_x = uv_w;
		uv_w = (1 / m_slice) * rad;


		vertices[vertex]._position = vertices[i + indexoffset]._position;
		vertices[vertex + 2]._position = vertices[i + indexoffset + 1]._position;

		vertices[vertex + 1]._uv = Vector2(uv_x, uv_y);
		vertices[vertex + 3]._uv = Vector2(uv_w, uv_y);
		vertices[vertex]._uv = Vector2(uv_x, uv_h);
		vertices[vertex + 2]._uv = Vector2(uv_w, uv_h);

		vertices[vertex]._normal = Vector3(vertices[i]._position._x, 0, vertices[i]._position._z);
		vertices[vertex + 1]._normal = Vector3(vertices[i]._position._x, 0, vertices[i]._position._z);
		vertices[vertex + 2]._normal = Vector3(vertices[i]._position._x, 0, vertices[i]._position._z);
		vertices[vertex + 3]._normal = Vector3(vertices[i]._position._x, 0, vertices[i]._position._z);


		indices[cr++] = vertex;
		indices[cr++] = vertex + 1;
		indices[cr++] = vertex + 2;
		indices[cr++] = vertex + 3;

		vertex += 4;
	}
	//最後は始点なので自力でｗｗ

	uv_x = uv_w;
	uv_w = 1;


	vertices[vertex + 3]._position = vertices[1]._position;
	vertices[vertex + 1]._position = vertices[vertex - 1]._position;

	vertices[vertex]._position = vertices[vertex - 2]._position;
	vertices[vertex + 2]._position = vertices[1 + indexoffset]._position;

	vertices[vertex + 1]._uv = Vector2(uv_x, uv_y);
	vertices[vertex + 3]._uv = Vector2(uv_w, uv_y);
	vertices[vertex]._uv = Vector2(uv_x, uv_h);
	vertices[vertex + 2]._uv = Vector2(uv_w, uv_h);

	vertices[vertex]._normal = Vector3(vertices[vertex - 2]._position._x, 0, vertices[vertex - 2]._position._z);
	vertices[vertex + 1]._normal = Vector3(vertices[vertex - 2]._position._x, 0, vertices[vertex - 2]._position._z);
	vertices[vertex + 2]._normal = Vector3(vertices[vertex - 2]._position._x, 0, vertices[vertex - 2]._position._z);
	vertices[vertex + 3]._normal = Vector3(vertices[vertex - 2]._position._x, 0, vertices[vertex - 2]._position._z);


	indices[cr++] = vertex;
	indices[cr++] = vertex + 1;
	indices[cr++] = vertex + 2;
	indices[cr++] = vertex + 3;


	// Set up the description of the static vertex buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof( VertexType)*m_vertexCount;
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

void Cylinder::FinalizeBuffers(){

}

void Cylinder::RenderBuffers(){
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