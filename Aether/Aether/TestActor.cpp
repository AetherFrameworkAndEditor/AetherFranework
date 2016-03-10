#include "TestActor.h"
#include <iostream>
using namespace aetherClass;
TestActor::TestActor()
{
}


TestActor::~TestActor()
{
}
//
bool TestActor::Initialize(){
	SetName("Player");
	
	SetIsCollide(true);

	LoadFBX("ModelData/Creepar.fbx", eAxisSystem::eAxisOpenGL);



	return true;
}

//
void TestActor::Update(){

}
//
void TestActor::DoCollide(){
	std::cout << "Õ“Ë" << std::endl;
}