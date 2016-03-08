#include "TestScene.h"
#include "TestScene2.h"
#include "MaterialShader.h"
#include "GameController.h"
#include "Light.h"
#include <iostream>
#include"IncludePrimitive.h"
#include"LightShader.h"
#include "Physics.h"
#include"Text.h"
#include"Font.h"



using namespace std;
using namespace aetherClass;
std::string TestScene::m_name = "Test";
TestScene::TestScene():
GameScene(m_name,GetManager())
{
}


TestScene::~TestScene()
{
}

int m_score;

Text *text;
Font *font;

bool TestScene::Initialize(){
	color = new PixelShader();
	camera = new ViewCamera();


	GameScene* scene = new TestScene2();
	RegisterScene(scene);

	ShaderDesc desc;
	desc._vertex._entryName = "vs_main";
	desc._vertex._srcFile = L"Shader/VertexShaderBase.hlsl";
	desc._pixel._entryName = "ps_main";
	desc._pixel._srcFile = L"Shader/Texture.ps";
	
	color->Initialize(desc, ShaderType::eVertex | ShaderType::ePixel);


	camera->Translation()._z = -50;


	FontDesc fontDesc;
	fontDesc._fontSize = 100;
	fontDesc._outputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc._clipPrecision = CLIP_DEFAULT_PRECIS;
	fontDesc._charSet = SHIFTJIS_CHARSET;
	fontDesc._fileName = L"font/apj.ttf";
	fontDesc._fontName = L"‚ ‚ñ‚¸‚à‚¶";
	
	font = new Font();
	_ASSERT_EXPR(font->Load(fontDesc),"ƒtƒHƒ“ƒgì‚ê‚È‚©‚Á‚½‚¼");
	
	text = new Text();
	text->Initialize();
	text->SetFont(font);
	text->GetColor() = Color(1,0,1,1);
	
	text->UpdateText(L"Score:"+(char)m_score);

	return true;
}

//
void TestScene::Render(){
	camera->Render();
	text->Render(color);
}


bool TestScene::Updater(){
	if(GameController::GetKey().IsKeyDown(DIK_UP)){
		m_score += 100;
		std::wstring str = L"Score:"+std::to_wstring(m_score);
		text->UpdateText(str);
		
	}
	
	GameController::GetMouse().Intersection(*camera);

	if (GameController::GetMouse().IsRightButtonTrigger()){
		POINT vec = GameController::GetMouse().GetMousePosition();
		text->GetTransform()._translation._x = vec.x;
		text->GetTransform()._translation._y = vec.y;
	}

	camera->Controller();

	return true;
}

void TestScene::Finalize(){
	color->Finalize();
	text->Finalize();
	font->Release();

	delete color;
	delete camera;
}