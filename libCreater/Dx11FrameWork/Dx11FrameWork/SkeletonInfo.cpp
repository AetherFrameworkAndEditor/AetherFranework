#include "SkeletonInfo.h"

using namespace aetherClass;
SkeletonInfo::SkeletonInfo()
{
	m_parent = nullptr;
	m_name = "null";
}


SkeletonInfo::~SkeletonInfo()
{
	if (m_parent)
	{
		delete m_parent;
		m_parent = nullptr;
	}

	for (auto index : m_children)
	{
		if (index)
		{
			delete index;
			index = nullptr;
		}
	}

	m_name = "null";
}

//
void SkeletonInfo::AddChild(SkeletonInfo* child){
	m_children.push_back(child);
}

//
void SkeletonInfo::SetParent(SkeletonInfo* parent){
	m_parent = parent;
}