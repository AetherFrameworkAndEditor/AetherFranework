#include "GameActorManager.h"
#include "Physics.h"
using namespace aetherClass;
GameActorManager::GameActorManager()
{
}


GameActorManager::~GameActorManager()
{
}

//
void GameActorManager::AddChild(GameActor* actor){
	m_children.push_back(actor);
}

//
void GameActorManager::Collide(){
	for (auto current : m_children)
	{
		// フラグがオフなら次のオブジェクト
		if (!current->GetIsCollide())
		{
			continue;
		}
		for (auto other : m_children)
		{
			// 同じ名前なら無視する
			if (current->GetName() == other->GetName())
			{
				continue;
			}

			// 衝突していたら衝突処理が呼ばれる
			// Box
			if (IsHitBoxCollider(current, other))
			{
				current->DoCollide();
			}

			// Sphere
			if (IsHitSphereCollider(current, other))
			{
				current->DoCollide();
			}
		}
	}
}

//
bool GameActorManager::IsHitBoxCollider(GameActor* current, GameActor* other){
	
	for (auto currentCollideBox : current->GetBoxCollide())
	{
		for (auto otherCollideBox : other->GetBoxCollide())
		{
			if (aetherFunction::CollideBoxOBB(*currentCollideBox, *otherCollideBox))
			{
				return true;
			}
		}
	}

	return false;
}

//
bool GameActorManager::IsHitSphereCollider(GameActor* current, GameActor* other){
	for (auto currentCollideBox : current->GetSphereCollide())
	{
		for (auto otherCollideBox : other->GetSphereCollide())
		{
			if (aetherFunction::ColliderBoxSphere(*currentCollideBox, *otherCollideBox))
			{
				return true;
			}
		}
	}

	return false;
}

//
void GameActorManager::RemoveChild(){
	for (auto index : m_children)
	{
		if (index)
		{
			index->Finlize();
			delete index;
			index = nullptr;
		}
	}
}