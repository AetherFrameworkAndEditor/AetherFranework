/******************************************************************************/
/*! @addtogroup aetherClass
@file      FbxMeshNode.h
@brief     FbxÇ©ÇÁì«Ç›éÊÇ¡ÇΩèÓïÒÇï€éùÇ∑ÇÈÇΩÇﬂÇÃÉNÉâÉX
*******************************************************************************
@date       2015/12/23
@author     ã¥ñ{çq
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

namespace aetherClass{
	struct FbxMeshNode
	{
		FbxMeshNode(){
			_vertex = nullptr;
			_index = nullptr;
			_vertexCount = 0;
			_indexCount = 0;
		}

		~FbxMeshNode(){
			Release();

		}
		std::vector<Material> _materialBuffer;

		VertexType* _vertex;
		unsigned long* _index;
		Matrix4x4 _matrix;
		Transform _transform;
		FbxKeyframeAnimationInfo _keyframeAnimation;
		unsigned long _vertexCount;
		unsigned long _indexCount;

	private:
		void Release(){
			_materialBuffer.clear();
			_vertexCount = 0;
			_indexCount = 0;
		}
	};
}
#endif