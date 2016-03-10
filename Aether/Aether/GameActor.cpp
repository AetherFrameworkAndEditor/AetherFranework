#include "GameActor.h"
using namespace aetherClass;

GameActor::GameActor()
{
	m_fbx = nullptr;
	m_model = nullptr;
	m_objectName = "Null";
	m_isCollide = true;
	property._transform._scale = 1;
	property._transform._rotation = 0;
	property._transform._translation = 0;
}


GameActor::~GameActor()
{
	if (m_fbx)
	{
		m_fbx->Finalize();
		delete m_fbx;
		m_fbx = nullptr;
	}

	//
	if (m_model)
	{
		m_model->Finalize();
		delete m_model;
		m_model = nullptr;
	}

	//
	if (m_boxCollide.size() >= 0)
	{
		for (auto index : m_boxCollide)
		{
			if (index)
			{
				index->Finalize();
				delete index;
				index = nullptr;
			}
		}
	}

	//
	if (m_sphereCollide.size() >= 0)
	{
		for (auto index : m_sphereCollide)
		{
			if (index)
			{
				index->Finalize();
				delete index;
				index = nullptr;
			}
		}
	}

	m_objectName = "Null";
	m_isCollide = true;
}

//
bool GameActor::LoadFBX(std::string path, eAxisSystem axis){
	m_fbx = new FbxModel();
	m_fbx->LoadFBX(path, axis);
	
	return true;
}

//
template<class ModelType>
bool GameActor::CreateModel(){
	bool result;
	m_model = new ModelType();
	result = m_model->Initialize();

	return result;
}

//
void GameActor::SetFbxTextureDirectory(std::string path){
	if (!m_fbx) return;
	m_fbx->SetTextureDirectoryName(path);
}


//
void GameActor::SetTexture(Texture* tex){
	if (!m_model) return;
	m_model->SetTexture(tex);
}

//
void GameActor::Render(ShaderBase* shader, bool collideRender){
	
	if (m_fbx)
	{
		m_fbx->property._transform = property._transform;
		m_fbx->Render(shader);
	}

	if (m_model)
	{
		m_model->property._transform = property._transform;
		m_model->Render(shader);
	}

	if (collideRender)
	{
		// Box
		for (auto index : m_boxCollide)
		{
			Transform move;
			move._rotation = property._transform._rotation;
			move._scale = index->property._transform._scale;
			Vector3 translation =  property._transform._translation - m_prevPosition;

			move._translation += translation;

			index->property._transform._rotation = move._rotation; // 回転
			index->property._transform._scale = move._scale;       // スケールは変わらない
			index->property._transform._translation += translation;// 移動
			index->Render(shader);
		}

		// Spehre
		for (auto index : m_sphereCollide)
		{
			Transform move;
			move._rotation = property._transform._rotation;
			move._scale = index->property._transform._scale;
			Vector3 translation = property._transform._translation - m_prevPosition;

			move._translation += translation;

			index->property._transform._rotation = move._rotation; // 回転
			index->property._transform._scale = move._scale;       // スケールは変わらない
			index->property._transform._translation += translation;// 移動
			index->Render(shader);
		}
	}
	m_prevPosition = property._transform._translation;
	return;
}

//
void GameActor::SetIsCollide(const bool flg){
	m_isCollide = flg;
}

//
bool GameActor::GetIsCollide()const{
	return m_isCollide;
}

//
void GameActor::SetName(const std::string name){
	m_objectName = name;
}

//
std::string GameActor::GetName()const{
	return m_objectName;
}

//
std::vector<Cube*> GameActor::GetBoxCollide(){
	return m_boxCollide;
}

void GameActor::SetCamera(ViewCamera* camera){
	//
	if (m_fbx)
	{
		m_fbx->SetCamera(camera);
	}

	//
	if (m_model)
	{
		m_model->SetCamera(camera);
	}

	//
	for (auto index : m_boxCollide)
	{
		if (index)
		{
			index->SetCamera(camera);
		}
	}

	//
	for (auto index : m_sphereCollide)
	{
		if (index)
		{
			index->SetCamera(camera);
		}
	}
}

//
std::vector<Sphere*> GameActor::GetSphereCollide(){
	return m_sphereCollide;
}

//
void GameActor::AddCollideObject(Cube* object){
	m_boxCollide.push_back(object);
	return;
}

//
void GameActor::AddCollideObject(Sphere* object){
	m_sphereCollide.push_back(object);
	return;
}

//
bool GameActor::Initialize(){
	return true;
}

//
void GameActor::DoCollide(){
	return;
}

//
void GameActor::Finlize(){
	return;
}