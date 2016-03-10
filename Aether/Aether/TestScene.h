#pragma once
#include "GameScene.h"
#include <iostream>
#include "FbxModel.h"
#include "PixelShader.h"
#include "ViewCamera.h"
#include "ModelBase.h"

#include "Sphere.h"
#include "Line.h"
class TestScene:
	public aetherClass::GameScene
{
public:
	TestScene();
	~TestScene();

	bool Initialize()override;
	void Render()override;
	bool Updater()override;
	void Finalize()override;


private:

	static std::string m_name;

};

