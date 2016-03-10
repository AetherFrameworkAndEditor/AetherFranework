#pragma once
#include "LoadScreen.h"
#include "ModelBase.h"
#include "ViewCamera.h"
#include "ShaderBase.h"
class TestLoadScreen:public aetherClass::LoadScreen
{
public:
	TestLoadScreen();
	~TestLoadScreen();
	void Initialize()override;
	void Run()override;
	bool WaitRun()override;
	void Finalize()override;
private:
	aetherClass::ModelBase* model;
	aetherClass::ViewCamera* camera;
	aetherClass::ShaderBase* shader;
};

