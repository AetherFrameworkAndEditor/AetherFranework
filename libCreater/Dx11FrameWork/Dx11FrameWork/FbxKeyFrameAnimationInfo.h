#ifndef _FBXANIMATIONINFO_H
#define _FBXANIMATIONINFO_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      FbxKeyframeAnimationInfo.h
@brief     Fbxからのアニメーション情報を取得

*******************************************************************************
@date       2015/12/27
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#include <string>
#include <vector>
#include <Windows.h>
#include "Transform.h"
#include <unordered_map>
namespace aetherClass{

	class FbxKeyframeAnimationInfo
	{
	public:
		FbxKeyframeAnimationInfo(){
			_parentMatrix.Identity();
			_animationLayerName = "Null";
		}
		~FbxKeyframeAnimationInfo(){
			_animationLayerName = "Null";
		}
		std::string _animationLayerName;
		Matrix4x4 _initMatrix;
		Matrix4x4 _parentMatrix;
		std::unordered_map<std::string, std::vector<Matrix4x4>> _keyframeHash;
	};
}
#endif