#include "TestScene.h"
#include "TestScene2.h"

#include <iostream>

#include "GameController.h"
#include"IncludePrimitive.h"
#include "Physics.h"
#include"Skybox.h"
#include "GameSound3D.h"
#include "GameSound.h"
using namespace std;
std::string TestScene::m_name = "Test";
TestScene::TestScene():
GameScene(m_name,GetManager())
{
}


TestScene::~TestScene()
{
}
void MoveController(FbxModel*);

std::shared_ptr<PixelShader>colorShader;
std::shared_ptr<PixelShader>textureShader;
std::shared_ptr<MaterialShader>materialShader;

std::shared_ptr<ViewCamera>camera;

std::shared_ptr<Sphere>m_sphere[2];
std::shared_ptr<Line> m_line;
std::shared_ptr<Skybox>skybox;
std::shared_ptr<Rectangle3D>model;

std::shared_ptr<FbxModel>m_fbx;

Light light;

std::shared_ptr<Text>text;
std::shared_ptr<Font>font;

std::map<std::string,Texture*>texture;
std::map<std::string, ModelBase*>models;

std::unique_ptr<GameSound3D> sound;
bool TestScene::Initialize(){
	RegisterScene(new TestScene2);
	camera = std::make_shared<ViewCamera>();
	m_sphere[0] = std::make_shared<Sphere>(15, 15);
	m_sphere[1] = std::make_shared<Sphere>(15, 15);


	GameScene* scene = new TestScene2();
	RegisterScene(scene);
	
	ShaderDesc desc;
	desc._vertex._entryName = "vs_main";
	desc._pixel._entryName = "ps_main";

	desc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";
	desc._pixel._srcFile = L"Shader/Texture.ps";
	
	colorShader = std::make_shared<PixelShader>();
	colorShader->Initialize(desc, ShaderType::eVertex | ShaderType::ePixel);

	desc._pixel._srcFile = L"Shader/Texture.ps";

	textureShader = std::make_shared<PixelShader>();
	textureShader->Initialize(desc, ShaderType::eVertex | ShaderType::ePixel);
	
	desc._vertex._srcFile = L"Shader/MaterialVS.hlsl";
	desc._pixel._srcFile = L"Shader/MaterialPS.hlsl";

	materialShader = std::make_shared<MaterialShader>();
	materialShader->Initialize(desc, ShaderType::eVertex | ShaderType::ePixel);
	materialShader->SetCamera(camera.get());
	materialShader->SetLight(&light);


	m_sphere[0]->Initialize();
	m_sphere[0]->SetCamera(camera.get());
	m_sphere[0]->property._transform._scale = 2;
	m_sphere[0]->property._color = Color(1.5f, 1.5f, 0.0f, 1.0f);

	m_sphere[1]->Initialize();
	m_sphere[1]->SetCamera(camera.get());
	m_sphere[1]->property._transform._scale = 2;
	m_sphere[1]->property._transform._translation._x = 10;
	m_sphere[1]->property._color = Color(1.5f, 0.0f, 0.0f, 1.0f);

	texture["Suede"] = new Texture();
	texture["Suede"]->Load("2d/Suede-bl.jpg");

	m_sphere[0]->SetTexture(texture["Suede"]);
	m_sphere[1]->SetTexture(texture["Suede"]);

	texture["NULL"] = new Texture();
	texture["NULL"]->Load("2d/banana.png");
 
	model = std::make_shared<Rectangle3D>();
	model->Initialize();
	model->SetCamera(camera.get());
	model->property._transform._translation._z = 10;
	model->property._transform._scale = 5;
	model->property._color = Color(0.2f, 0.2f, 0.0f, 1.0f);
	camera->property._translation._z = -50;

	model->SetTexture(texture["NULL"]);

	skybox = std::make_shared<Skybox>();
	skybox->Initialize();
	skybox->SetCamera(camera.get());

	texture["Skybox"] = new Texture();
	texture["Skybox"]->Load("2d/sunset.png");
	skybox->SetTexture(texture["Skybox"]);

	m_fbx = std::make_shared<FbxModel>();
	m_fbx->LoadFBX("ModelData/testmodel.fbx", eAxisSystem::eAxisOpenGL);
	m_fbx->SetCamera(camera.get());
	m_fbx->property._transform._scale._z = -1;
	m_fbx->SetTextureDirectoryName("2d");


	FontDesc fontDesc;
	fontDesc._fontSize = 50;
	fontDesc._charSet = SHIFTJIS_CHARSET;
	fontDesc._fileName = L"font/apj.ttf";
	fontDesc._fontName = L"あんずもじ";
	
	font = std::make_shared<Font>();
	if (!font->Load(fontDesc)){
		_ASSERT_EXPR(false, "フォント作れなかったぞ");
	}
	text = std::make_shared<Text>();
	text->Initialize();
	text->SetFont(font.get());
	text->property._color = Color(1, 0.7, 0.5, 1);
	
	if (!text->UpdateText(L"New ワールド＼(^0^)/")){
		_ASSERT_EXPR(false, L"FAAAAAAAAAAAACK");
	}

	sound = std::make_unique<GameSound3D>();
	
	sound->Load("Sound\\SE.wav");
	sound->SetSpeed(eSoundSpeed::eHighSpeed);
	sound->PlayToOneTime();
	return true;
}

//
void TestScene::Render(){
	DirectXEntity entity;
	entity.GetDirect3DManager()->SetTargetWindow(L"First");
	camera->Render();
	skybox->Render(colorShader.get());

	m_sphere[0]->Render(colorShader.get());

	entity.GetDirect3DManager()->SetTargetWindow(L"Second");
	
	m_sphere[1]->Render(colorShader.get());
	model->Render(colorShader.get());
	if (m_line)m_line->Render(colorShader.get());

	m_fbx->Render(materialShader.get());
	text->Render(colorShader.get());

}


bool TestScene::Updater(){
	static Color col2;
	if (GameController::GetKey().IsKeyDown(DIK_R)){
		col2._red += 0.01;
		ChangeScene("Test2", LoadState::eUnuse, LoadWaitState::eUnuse);
	}
	if (GameController::GetKey().IsKeyDown(DIK_G)){
		col2._green += 0.01;
	}
	if (GameController::GetKey().IsKeyDown(DIK_B)){
		col2._blue += 0.01;
	}
	if (GameController::GetKey().IsKeyDown(DIK_LCONTROL)){
		if (GameController::GetKey().IsKeyDown(DIK_R)){
			col2 = Color();
		}
	}
	skybox->property._color = col2;
	MoveController(m_fbx.get());
	Vector3 hitPos;
	if (aetherFunction::ColliderBoxSphere(*m_sphere[0], *m_sphere[1],&hitPos)){
		cout << "HIT\n";
		cout << hitPos._x << "\tx\n";
		cout << hitPos._y << "\tx\n";
		cout << hitPos._z << "\tx\n\n";
		m_sphere[1]->property._transform._translation += hitPos;
	}

	
	GameController::GetMouse().Intersection(*camera);

	if (GameController::GetMouse().IsRightButtonTrigger()){
		POINT vec = GameController::GetMouse().GetMousePosition();
		text->property._transform._translation._x = vec.x;
		text->property._transform._translation._y = vec.y;
	}
	if (GameController::GetMouse().IsLeftButtonTrigger())
	{
		cout << "In";
		m_line = make_shared<Line>(GameController::GetMouse().GetDirection(), 10);
		m_line->Initialize();
		m_line->SetCamera(camera.get());
		m_line->property._color._green = 1;
		m_line->property._transform._scale = 10;

		m_line->property._transform._translation = camera->property._translation;

		//cout << "LeftButtonDown" << endl;

		Vector3 rayOrigin;
		Vector3 rayDirection;

		rayOrigin = GameController::GetMouse().GetOrigin();
		rayDirection = GameController::GetMouse().GetDirection();


		if (aetherFunction::RaySphereIntersect(*m_sphere[0], rayOrigin, rayDirection,1000))
		{
			cout << "Clicked!" << endl;

		}
	//	model->VertexData();

	}
	static float rad = 0;
	const int LightDir = 100;
	rad++;
	//light.Translation()._x = cos(rad*kAetherRadian)*LightDir;
	//light.Translation()._z = sin(rad*kAetherRadian)*LightDir;



	camera->Controller();
	camera->Controller();
	camera->Controller();
	camera->Controller();
	camera->Controller();
	camera->Controller();
	camera->Controller(); 
	camera->Controller();
	camera->Controller();
	camera->Controller();
	camera->Controller();
	camera->Controller();
	camera->Controller();

	camera->Controller();


	return true;
}

void TestScene::Finalize(){
	colorShader->Finalize();
	textureShader->Finalize();
	materialShader->Finalize();
	m_fbx->Finalize();
	m_sphere[0]->Finalize();
	m_sphere[1]->Finalize();

	text->Finalize();
	font->Release();

	for each (auto tex in texture)
	{
		delete tex.second;
	}
	texture.clear();

}

void MoveController(FbxModel* model){
	Vector3 direc;
	const float moveVol = 0.2;

	if (GameController::GetKey().IsKeyDown(DIK_UP)){
		direc._z += moveVol;
	}
	else if (GameController::GetKey().IsKeyDown(DIK_DOWN)){
		direc._z -= moveVol;
	}
	if (GameController::GetKey().IsKeyDown(DIK_RIGHT)){
		direc._x += moveVol;
	}
	else if (GameController::GetKey().IsKeyDown(DIK_LEFT)){
		direc._x -= moveVol;
	}
	if (GameController::GetKey().IsKeyDown(DIK_COLON)){
		direc._y += moveVol;
	}
	else if (GameController::GetKey().IsKeyDown(DIK_BACKSLASH)){
		direc._y -= moveVol;
	}
	model->property._transform._scale += direc;

}



