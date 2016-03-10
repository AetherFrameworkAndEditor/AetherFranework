#pragma once
#include "TestScene2.h"
using namespace aetherClass;

	bool TestScene2::Initialize(){
		std::cout << "Initalize2" << std::endl;
		_fadeIn= new aetherClass::Rectangle3D();
		_fadeOut = new aetherClass::Rectangle3D();
		_shader = new PixelShader();
		_cameraw = new ViewCamera();
		_cameraw->property._translation._z = -50;

		ShaderDesc desc;
		desc._vertex._entryName = "vs_main";
		desc._vertex._srcFile = L"Shader/BasicColor.vs";
		desc._pixel._entryName = "ps_main";
		desc._pixel._srcFile = L"Shader/BasicColor.ps";
		_shader->Initialize(desc, ShaderType::eVertex | ShaderType::ePixel);

		_fadeIn->Initialize();
		_fadeIn->property._color._alpha = 0;
		_fadeIn->SetCamera(_cameraw);
		_fadeIn->property._transform._scale *= 1000;
		_fadeIn->property._transform._translation._z = -45;

		_fadeOut->Initialize();
		_fadeOut->property._color._alpha = 1;
		_fadeOut->SetCamera(_cameraw);
		_fadeOut->property._transform._scale *= 1000;
		_fadeOut->property._transform._translation._z = -45;
		GameScene* scene = new TestScene();
		RegisterScene(scene);
		return true;
	}

	//
	void TestScene2::Render(){
	

	}

	//
	bool TestScene2::Updater(){
	
		if (GameController::GetKey().IsKeyDown(DIK_R)){

			ChangeScene("Test", LoadState::eUnuse, LoadWaitState::eUnuse);
		}
		return true;
	}

	//
	void TestScene2::Finalize(){

	}

	//
	bool TestScene2::TransitionIn(){
		_cameraw->Render();
		_fadeIn->property._color._alpha += 0.01f;
		_fadeIn->Render(_shader);
		std::cout << "in" << std::endl;
		if (_fadeIn->property._color._alpha < 1.0f)
		{

			return kTransitionning;
		}

		return kTransitionEnd;
	}

	//
	bool TestScene2::TransitionOut(){
		_cameraw->Render();
		_fadeOut->property._color._alpha -= 0.01f;
		_fadeOut->Render(_shader);
		std::cout << "out" << std::endl;
		if (_fadeOut->property._color._alpha > 0)
		{
			return kTransitionning;
		}
		std::cout << "End" << std::endl;
		return kTransitionEnd;
	}


