/******************************************************************************/
/*! @addtogroup aetherClass
@file      VertexType.h
@brief     �`�掞�Ɏg�p�������ۑ�����N���X

*******************************************************************************
@date       2015/12/23 22:35
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/23 22:35 ���{�q
-# Initial Version
- 2015/12/26 01:33 ���q�a��
-# Did something lol. And deleted CopyConstructor.
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