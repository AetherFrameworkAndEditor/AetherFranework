
#include <iostream>
#include <assert.h>
#include "FbxModel.h"
#include "Direct3DManager.h"
#include "ViewCamera.h"
#include "ModelUtility.h"
#include "FbxUtility.h"
using namespace aetherClass;
FbxModel::FbxModel()
{
	m_fbxLoader = nullptr;
	this->property._transform._scale = Vector3(1, 1, 1);
}


//
bool FbxModel::LoadFBX(std::string file, eAxisSystem axis){

	bool result;
	m_modelPath = file;
	// read start fbx file 
	m_fbxLoader = std::make_unique<FbxLoader>();
	result = m_fbxLoader->Load(file, axis);
	if (!result)
	{
		return false;
	}

	// Initalize
	result = LoadModelBuffers(GetDirect3DManager());
	if (!result)
	{
		return false;
	}

	return true;
}

//
bool FbxModel::LoadModelBuffers(Direct3DManager* directX){
	HRESULT result;

	const int meshNodeCount = m_fbxLoader->GetNodeMesh().size();

	// メッシュのノードごとに作成するので、メッシュのノード分確保
	m_nodeMeshBuffer.resize(meshNodeCount);

	// メッシュの子供の数だけ繰り返す
	for (int i = 0; i < meshNodeCount; ++i){
		// Create Basecolor constant buffers.
		directX->GetDevice()->CreateBuffer(&aetherFunction::GetConstantBufferDesc(sizeof(Color)), NULL, &m_nodeMeshBuffer[i]._colorBuffer);
		directX->GetDevice()->CreateBuffer(&aetherFunction::GetConstantBufferDesc(sizeof(MaterialBufferType)), NULL, &m_nodeMeshBuffer[i]._materialBuffer);

		const int vertexCount = m_fbxLoader->GetNodeMesh()[i]._vertexCount;
		m_nodeMeshBuffer[i]._vertexCount = vertexCount;

		D3D11_BUFFER_DESC vertexBufferDesc;
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(VertexType) * vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA vertexData;
		vertexData.pSysMem = m_fbxLoader->GetNodeMesh()[i]._vertex;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		result = directX->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_nodeMeshBuffer[i]._vertexBuffer);
		if (FAILED(result))
		{
			MessageBox(NULL, L"Could not created vertexBuffer", L"Error", MB_OK);
			return false;
		}

		delete[] m_fbxLoader->GetNodeMesh()[i]._vertex;
		m_fbxLoader->GetNodeMesh()[i]._vertex = nullptr;

		const unsigned long indexCount = m_fbxLoader->GetNodeMesh()[i]._indexCount;
		m_nodeMeshBuffer[i]._indexCount = indexCount;
	
		D3D11_BUFFER_DESC indexBufferDesc;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(unsigned long)*indexCount;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA indexData;
		indexData.pSysMem = m_fbxLoader->GetNodeMesh()[i]._index;
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		result = directX->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_nodeMeshBuffer[i]._indexBuffer);

		if (FAILED(result))
		{
			MessageBox(NULL, L"Could not created index buffer", L"Error", MB_OK);
			return false;
		}

		delete[] m_fbxLoader->GetNodeMesh()[i]._index;
		m_fbxLoader->GetNodeMesh()[i]._index = nullptr;
		m_nodeMeshBuffer[i].property._transform = m_fbxLoader->GetNodeMesh()[i]._transform;
		m_nodeMeshBuffer[i].property._material = m_fbxLoader->GetNodeMesh()[i]._materialBuffer[0];

		// 行列の取得
		m_nodeMeshBuffer[i]._meshMatrix = m_fbxLoader->GetNodeMesh()[i]._matrix;

		bool nodeResult = false;
		nodeResult = LoadNodeMesh();

		if (!nodeResult)
		{
			return false;
		}

		// キーフレームアニメーションの読み取り
		const int maxSize = m_fbxLoader->GetNodeMesh()[i]._keyframeAnimation._rotation.size();
		m_nodeMeshBuffer[i]._animationTransform.resize(maxSize);
		for (int index = 0; index < maxSize; ++index)
		{
			m_nodeMeshBuffer[i]._animationTransform[index]._translation = m_fbxLoader->GetNodeMesh()[i]._keyframeAnimation._trancelation[index]._data;
			m_nodeMeshBuffer[i]._animationTransform[index]._rotation = m_fbxLoader->GetNodeMesh()[i]._keyframeAnimation._rotation[index]._data;
			m_nodeMeshBuffer[i]._animationTransform[index]._scale = m_fbxLoader->GetNodeMesh()[i]._keyframeAnimation._scaling[index]._data;
		}


	}

	return true;
}

//
void FbxModel::Finalize()
{
	if (m_fbxLoader)
	{
		m_fbxLoader.release();
		m_fbxLoader = nullptr;
	}

	if (m_nodeMeshBuffer.size() > 0)
	{
		for (auto index : m_nodeMeshBuffer)
		{
			index.Release();
		}
	}
	return;
}

//
void FbxModel::Render(ShaderBase* shader){

	for (int id = 0; id < m_nodeMeshBuffer.size(); ++id){

		NodeRender(shader, id);

	}
	return;
}

//
void FbxModel::NodeRender(ShaderBase* shader, const int id){

	RenderBuffers(GetDirect3DManager(), m_nodeMeshBuffer[id]);

	Matrix4x4 zMatrix;
	zMatrix.RightToLeftIdentity();


	// 各ノードの行列
	Matrix4x4 nodeMatrix = m_nodeMeshBuffer[id]._meshMatrix;

	// トランスフォームからマトリックスを生成
	Matrix4x4 transMatrix = property._transform.Transmatrix();

	// カメラのビュー行列の取得
	Matrix4x4 view = m_camera->GetViewMatrix();

	// プロジェクション行列の取得
	Matrix4x4 projection = GetDirect3DManager()->GetProjectionMatrix();

	// コンスタントバッファーに登録
	// デフォルトはカラー
	CreateConstantBuffers(m_nodeMeshBuffer[id]);

	// ノードのマトリックスとトランスフォームのマトリックスを掛け合わせる
	Matrix4x4 mixMatrix = nodeMatrix*transMatrix;

	// シェーダーを用いて描画
	shader->Render(m_nodeMeshBuffer[id]._indexCount, mixMatrix, view, projection);
	return;
}

//
void FbxModel::KeyFrameAnimation(ShaderBase* shader){
	static int animation = 0;

	for (auto node : m_nodeMeshBuffer){

		// アニメーションなければ無視
		if (node._animationTransform.size() <= 0)
		{
			continue;
		}

		if (animation >= node._animationTransform.size())
		{
			animation = 0;
		}

		RenderBuffers(GetDirect3DManager(), node);


		// 各ノードの姿勢行列
		Matrix4x4  nodeMatrix = node._meshMatrix;

		Matrix4x4 view = m_camera->GetViewMatrix();
		Matrix4x4 projection = GetDirect3DManager()->GetProjectionMatrix();

		// ワールド行列の作成
		Matrix4x4 hoge = node._animationTransform[animation].Transmatrix();

		// アニメーション用トランスフォーム
		Transform animationTransform;

		// 移動行列の作成
		Matrix4x4 translateMatrix;
		animationTransform._translation = node._animationTransform[animation]._translation + node.property._transform._translation;
		translateMatrix.TranslateMatrix(animationTransform._translation);

		// 回転行列の作成
		Matrix4x4 rotationMatrix;
		animationTransform._rotation = node._animationTransform[animation]._rotation + node.property._transform._rotation;
		rotationMatrix.PitchYawRoll(animationTransform._rotation);


		// スケール行列の作成
		Matrix4x4 scaleMatrix;
		animationTransform._scale = node._animationTransform[animation]._scale + node.property._transform._scale;
		scaleMatrix.ScaliMatrix(animationTransform._scale);
		scaleMatrix.Identity();

		// トランスフォームから行列を作成
		Matrix4x4 transformMatrix = property._transform.Transmatrix();

		Matrix4x4 animationMatrix = nodeMatrix*scaleMatrix*rotationMatrix*translateMatrix*transformMatrix;
		CreateConstantBuffers(node);

		shader->Render(node._indexCount, animationMatrix, view, projection);
		animation += 1;
	}
}

//
ID3D11ShaderResourceView* FbxModel::GetTexture(const int id){
	return m_nodeMeshBuffer[id].GetTexture();
}

//
void FbxModel::CreateConstantBuffers(Mesh mesh){
	D3D11_MAPPED_SUBRESOURCE mapped;
	Color *dataptr;
	MaterialBufferType *dataptr2;
	unsigned int bufferNumber;

	// カラーの登録
	GetDirect3DManager()->GetDeviceContext()->Map(mesh._colorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	dataptr = (Color*)mapped.pData;
	*dataptr = mesh.property._color;
	GetDirect3DManager()->GetDeviceContext()->Unmap(mesh._colorBuffer, 0);
	bufferNumber = 0;
	GetDirect3DManager()->GetDeviceContext()->PSSetConstantBuffers(bufferNumber, 1, &mesh._colorBuffer);

	bufferNumber = 1;
	GetDirect3DManager()->GetDeviceContext()->Map(mesh._materialBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);

	// マテリアル情報の登録
	dataptr2 = (MaterialBufferType*)mapped.pData;
	dataptr2->_diffuse = mesh.property._material._diffuse._color;
	dataptr2->_specular = mesh.property._material._specular._color;
	dataptr2->_ambient = mesh.property._material._ambient._color;
	dataptr2->_emissive = mesh.property._material._emissive._color;
	dataptr2->_specularPower = mesh.property._material._specularPower;
	dataptr2->_shininess = mesh.property._material._shininess;
	dataptr2->_transparencyFactor = mesh.property._material._transparencyFactor;

	GetDirect3DManager()->GetDeviceContext()->Unmap(mesh._materialBuffer, 0);
	GetDirect3DManager()->GetDeviceContext()->PSSetConstantBuffers(bufferNumber, 1, &mesh._materialBuffer);

	// テクスチャがあればそれも使う
	// とりあえずディヒューズだけ
	if (mesh.property._material._diffuse._texture){
		ID3D11ShaderResourceView* tex = mesh.property._material._diffuse._texture->GetTexture();
		ID3D11SamplerState* sampler = mesh.property._material._diffuse._texture->GetSamplerState();

		GetDirect3DManager()->GetDeviceContext()->PSSetSamplers(0, 1, &sampler);
		GetDirect3DManager()->GetDeviceContext()->PSSetShaderResources(0, 1, &tex);
	}
	else{
		ID3D11ShaderResourceView* tex = nullptr;
		GetDirect3DManager()->GetDeviceContext()->PSSetShaderResources(0, 1, &tex);
	}

}

//
bool FbxModel::SetTexture(Texture* texture, eMatrerialType type){
	bool result;

	for (int id = 0; id < m_nodeMeshBuffer.size(); ++id)
	{
		SetNodeTexture(texture, id, type);
	}
	return true;
}

//
bool FbxModel::SetNodeTexture(Texture* texture, const int id, eMatrerialType type){
	bool result;

	switch (type)
	{
	case eMatrerialType::eAmbient:
		if (m_nodeMeshBuffer[id].property._material._ambient._texture)
		{
			delete m_nodeMeshBuffer[id].property._material._ambient._texture;
			m_nodeMeshBuffer[id].property._material._ambient._texture = nullptr;
		}
		m_nodeMeshBuffer[id].property._material._ambient._texture = texture;
		break;

	case eMatrerialType::eDiffuse:
		if (m_nodeMeshBuffer[id].property._material._diffuse._texture)
		{
			delete m_nodeMeshBuffer[id].property._material._diffuse._texture;
			m_nodeMeshBuffer[id].property._material._diffuse._texture = nullptr;
		}
		m_nodeMeshBuffer[id].property._material._diffuse._texture = texture;
		break;

	case eMatrerialType::eEmissive:
		if (m_nodeMeshBuffer[id].property._material._emissive._texture)
		{
			delete m_nodeMeshBuffer[id].property._material._emissive._texture;
			m_nodeMeshBuffer[id].property._material._emissive._texture = nullptr;
		}
		m_nodeMeshBuffer[id].property._material._emissive._texture = texture;
		break;

	case eMatrerialType::eSpecular:
		if (m_nodeMeshBuffer[id].property._material._specular._texture)
		{
			delete m_nodeMeshBuffer[id].property._material._specular._texture;
			m_nodeMeshBuffer[id].property._material._specular._texture = nullptr;
		}
		m_nodeMeshBuffer[id].property._material._specular._texture = texture;
		break;
	default:
		break;
	}

	return true;

}

//
void FbxModel::SetTextureDirectoryName(std::string directryName){
	for (int id = 0; id < m_nodeMeshBuffer.size(); ++id)
	{

		// アンビエントテクスチャの読み込み
		std::string ambientPath = aetherFunction::GetMaterialTextureName(directryName, m_nodeMeshBuffer[id].property._material._ambient);
		if (ambientPath != "null")
		{
			m_nodeMeshBuffer[id].property._material._ambient._texture = new Texture();
			m_nodeMeshBuffer[id].property._material._ambient._texture->Load(ambientPath);
		}

		// ディヒューズテクスチャの読み込み
		std::string diffusePath = aetherFunction::GetMaterialTextureName(directryName, m_nodeMeshBuffer[id].property._material._diffuse);
		if (diffusePath != "null")
		{
			m_nodeMeshBuffer[id].property._material._diffuse._texture = new Texture();
			m_nodeMeshBuffer[id].property._material._diffuse._texture->Load(diffusePath);
		}

		// エミッシブテクスチャの読み込み
		std::string emissivePath = aetherFunction::GetMaterialTextureName(directryName, m_nodeMeshBuffer[id].property._material._emissive);
		if (emissivePath != "null")
		{
			m_nodeMeshBuffer[id].property._material._emissive._texture = new Texture();
			m_nodeMeshBuffer[id].property._material._emissive._texture->Load(emissivePath);
		}

		// スペキュラーテクスチャの読み込み
		std::string specularPath = aetherFunction::GetMaterialTextureName(directryName, m_nodeMeshBuffer[id].property._material._specular);
		if (specularPath != "null")
		{
			m_nodeMeshBuffer[id].property._material._specular._texture = new Texture();
			m_nodeMeshBuffer[id].property._material._specular._texture->Load(specularPath);
		}
	}

}
//
void FbxModel::SetCamera(ViewCamera* camera){
	m_camera = camera;
}

//
void FbxModel::SetModelMaterialColor(Color rgba, const int nodeID, eMatrerialType type){
	switch (type)
	{
	case eMatrerialType::eAmbient:
		m_nodeMeshBuffer[nodeID].property._material._ambient._color = rgba;
		break;

	case eMatrerialType::eDiffuse:
		m_nodeMeshBuffer[nodeID].property._material._diffuse._color = rgba;
		break;

	case eMatrerialType::eEmissive:
		m_nodeMeshBuffer[nodeID].property._material._emissive._color = rgba;
		break;

	case eMatrerialType::eSpecular:
		m_nodeMeshBuffer[nodeID].property._material._specular._color = rgba;
		break;
	default:
		break;
	}

	return;
}

void FbxModel::SetModelMaterialColor(Color rgba, eMatrerialType type){
	for (int i = 0; i < m_nodeMeshBuffer.size(); ++i)
	{
		switch (type)
		{
		case eMatrerialType::eAmbient:
			m_nodeMeshBuffer[i].property._material._ambient._color = rgba;
			break;

		case eMatrerialType::eDiffuse:
			m_nodeMeshBuffer[i].property._material._diffuse._color = rgba;
			break;

		case eMatrerialType::eEmissive:
			m_nodeMeshBuffer[i].property._material._emissive._color = rgba;
			break;

		case eMatrerialType::eSpecular:
			m_nodeMeshBuffer[i].property._material._specular._color = rgba;
			break;
		default:
			break;
		}

	}
}


//
void FbxModel::RenderBuffers(Direct3DManager* directX, Mesh mesh){
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	directX->GetDeviceContext()->IASetVertexBuffers(0, 1, &mesh._vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	directX->GetDeviceContext()->IASetIndexBuffer(mesh._indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	directX->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

std::string FbxModel::GetModelPath()const{
	return m_modelPath;
}