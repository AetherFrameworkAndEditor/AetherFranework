#ifndef _FBXANIMATIONINFO_H
#define _FBXANIMATIONINFO_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      FbxKeyframeAnimationInfo.h
@brief     Fbx����̃A�j���[�V���������擾

*******************************************************************************
@date       2015/12/27
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/27 ���{�q
-# Initial Version
******************************************************************************/
#include <string>
#include <vector>
#include <Windows.h>
#include "Transform.h"
namespace aetherClass{

	struct AnimationVector{
		Vector3 _data;
		float _frameSecounds;
	};

	class FbxKeyframeAnimationInfo
	{
	public:
		FbxKeyframeAnimationInfo(){
			_animationName = "Null";
			_animationLayerName = "Null";
			SecureZeroMemory(&_trancelation, sizeof(_trancelation));
			SecureZeroMemory(&_rotation, sizeof(_rotation));
			SecureZeroMemory(&_scaling, sizeof(_scaling));
		}
		~FbxKeyframeAnimationInfo(){
			_animationName = "Null";
			_animationLayerName = "Null";
			SecureZeroMemory(&_trancelation, sizeof(_trancelation));
			SecureZeroMemory(&_rotation, sizeof(_rotation));
			SecureZeroMemory(&_scaling, sizeof(_scaling));
		}

		std::string _animationName;
		std::string _animationLayerName;
		
		std::vector<AnimationVector> _trancelation;
		std::vector<AnimationVector> _rotation;
		std::vector<AnimationVector> _scaling;

		

	};
}
#endif