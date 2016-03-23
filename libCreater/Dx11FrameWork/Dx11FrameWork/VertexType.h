/******************************************************************************/
/*! @addtogroup aetherClass
@file      VertexType.h
@brief     描画時に使用する情報を保存するクラス

*******************************************************************************
@date       2015/12/23
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _VERTEXTYPE_H
#define _VERTEXTYPE_H

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace aetherClass{
	class VertexType
	{
		public:
			VertexType();
			~VertexType();

		public:
			Vector3 _position;
			Vector2 _uv;
			Vector3 _normal;
	};
}
#endif