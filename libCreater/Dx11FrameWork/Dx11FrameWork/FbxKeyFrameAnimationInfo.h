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

	struct AnimationVector{
		Vector3 _data;
		float _frameSecounds;
	};

	struct KeyframeArray{
		std::vector<AnimationVector> _trancelation;
		std::vector<AnimationVector> _rotation;
		std::vector<AnimationVector> _scaling;
		int _size;
		void Reset(){
			_rotation.clear();
			_scaling.clear();
			_trancelation.clear();
			_size = NULL;
		}
	};


	class FbxKeyframeAnimationInfo
	{
	public:
		FbxKeyframeAnimationInfo(){

			_animationLayerName = "Null";
		}
		~FbxKeyframeAnimationInfo(){
			_animationLayerName = "Null";
		}
		std::string _animationLayerName;
		std::unordered_map<std::string, KeyframeArray> _keyframeHash;
		std::vector<std::string> _keyframeNameList;

	};
}
#endif