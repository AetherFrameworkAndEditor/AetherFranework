/******************************************************************************/
/*! @addtogroup aetherClass
@file      SkeletonInfo.h
@brief     ボーンの情報を保持するクラス

*******************************************************************************
@date       2016/01/16
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

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
		std::string m_name;  // スケルトン名
		SkeletonInfo* m_parent;   // 親スケルトン
		std::vector<SkeletonInfo*> m_children; // 子ボーン

	};
}
#endif