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
		// �t���O���I�t�Ȃ玟�̃I�u�W�F�N�g
		if (!current->GetIsCollide())
		{
			continue;
		}
		for (auto other : m_children)
		{
			// �������O�Ȃ疳������
			if (current->GetName() == other->GetName())
			{
				continue;
			}

			// �Փ˂��Ă�����Փˏ������Ă΂��
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