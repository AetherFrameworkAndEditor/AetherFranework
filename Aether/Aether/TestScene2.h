#pragma once
#include "GameScene.h"
#include <iostream>
#include "ModelBase.h"
#include "Rectangle3D.h"
#include "PixelShader.h"
#include "GameController.h"
#include "TestScene.h"
using namespace aetherClass;

	class TestScene2 :public aetherClass::GameScene
	{
	private:
		ModelBase* _fadeIn;
		ModelBase* _fadeOut;
		ShaderBase* _shader;
		ViewCamera* _cameraw;
	public:
		TestScene2():
			GameScene("Test2", GetManager()){}
		~TestScene2(){}

		bool Initialize()override;

		void Render()override;

		bool Updater()override;

		void Finalize()override;
		bool TransitionIn()override;
		bool TransitionOut()override;
	};

