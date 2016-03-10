#include "TestActor2.h"

using namespace aetherClass;
TestActor2::TestActor2()
{
}


TestActor2::~TestActor2()
{
}

bool TestActor2::Initialize(){
	SetName("Null");
	SetIsCollide(true);

	LoadFBX("ModelData/Creepar.fbx", eAxisSystem::eAxisOpenGL);

	Cube* collide = new Cube();
	collide->Initialize();

	AddCollideObject(collide);

	return true;
}

//
void TestActor2::Update(){

}
//
void TestActor2::DoCollide(){

}