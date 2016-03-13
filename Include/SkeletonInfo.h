/******************************************************************************/
/*! @addtogroup aetherClass
@file      SkeletonInfo.h
@brief     �{�[���̐e�q�֌W���Ǘ�����N���X

*******************************************************************************
@date       2016/01/16
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/01/16 14:53 ���{�q
-# Initial Version
******************************************************************************/
#ifndef _SKELETONINFO_H
#define _SKELETONINFO_H
#include <vector>
#include <string>
namespace aetherClass{
	class SkeletonInfo
	{
	public:
		SkeletonInfo();
		~SkeletonInfo();

		void AddChild(SkeletonInfo*);

		void SetParent(SkeletonInfo*);

	public:
		std::string m_name;  // �X�P���g����
		SkeletonInfo* m_parent;   // �e�X�P���g��
		std::vector<SkeletonInfo*> m_children; // �q�{�[��

	};
}
#endif