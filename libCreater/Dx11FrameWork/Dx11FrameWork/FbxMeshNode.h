/******************************************************************************/
/*! @addtogroup aetherClass
@file      FbxMeshNode.h
@brief     Fbx����ǂݎ��������ێ����邽�߂̃N���X
*******************************************************************************
@date       2015/12/23
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _FBXMESHNODE_H
#define _FBXMESHNODE_H

#include <Windows.h>
#include <vector>
#include "VertexType.h"
#include "Matrix4x4.h"
#include "Transform.h"
#include "Material.h"
#include "FbxKeyFrameAnimationInfo.h"
#include "FbxBoneInfo.h"
namespace aetherClass{
	struct FbxMeshNode
	{
		FbxMeshNode(){
			_vertexBuffer = nullptr;
			_indexBuffer = nullptr;
			_materialBuffer.clear();
			
			SecureZeroMemory(&_matrix, sizeof(_matrix));
			SecureZeroMemory(&_transform, sizeof(_transform));
			_vertexCount = 0;
			_indexCount = 0;
		}

		VertexType* _vertexBuffer;
		unsigned long* _indexBuffer;
		std::vector<aetherClass::Material> _materialBuffer;

		Matrix4x4 _matrix;
		Transform _transform;
		FbxKeyframeAnimationInfo _keyframeAnimation;
		SkinInfo _skinInfo;

		unsigned int _vertexCount;
		unsigned long _indexCount;
	};
}
#endif