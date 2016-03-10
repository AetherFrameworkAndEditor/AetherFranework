#include "TestLoadScreen.h"
#include "Rectangle3D.h"
#include "PixelShader.h"
#include "GameController.h"
#include <iostream>
using namespace aetherClass;
TestLoadScreen::TestLoadScreen()
{
}


TestLoadScreen::~TestLoadScreen()
{
}

void TestLoadScreen::Initialize(){
	model = new aetherClass::Rectangle3D();
	camera = new aetherClass::ViewCamera();
	camera->property._translation._z = -50;
	shader = new aetherClass::PixelShader();
	model->Initialize();
	model->SetCamera(camera);

	model->property._color._blue = 1;
	model->property._color._alpha = 1;
	model->property._transform._translation._z = -49;
	model->property._transform._scale *= 10000;

	ShaderDesc desc;
	desc._vertex._entryName = "vs_main";
	desc._vertex._srcFile = L"Shader/BasicColor.vs";
	desc._pixel._entryName = "ps_main";
	desc._pixel._srcFile = L"Shader/BasicColor.ps";
	shader->Initialize(desc, ShaderType::eVertex | ShaderType::ePixel);
}

bool TestLoadScreen::WaitRun(){
	std::cout << "”CˆÓ‚Ìˆ—‚Ü‚¿" << std::endl;
	GameController::GetKey().Read();
	if (GameController::GetKey().IsKeyDown(DIK_SPACE))
	{
		std::cout << "”CˆÓ‚Ìˆ—ŽÀs" << std::endl;
		return kWaitEnd;
	}
	int a(10);
	return kWaitting;
}

//
void TestLoadScreen::Run(){
	camera->Render();
	model->Render(shader);

	std::cout << "ƒ[ƒh" << std::endl;
}
void TestLoadScreen::Finalize(){

}