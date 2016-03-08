/******************************************************************************/
/*! @addtogroup aetherClass
@file      VertexType.h
@brief     描画時に使用する情報を保存するクラス

*******************************************************************************
@date       2015/12/23 22:35
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/23 22:35 橋本航
-# Initial Version
- 2015/12/26 01:33 金子和樹
-# Member initialized in NULL
******************************************************************************/


#include "VertexType.h"
#include<stddef.h>
using namespace aetherClass;

VertexType::VertexType()
{
	_position = NULL;
	_uv = NULL;
	_normal = NULL;
}


VertexType::~VertexType()
{
	_position = NULL;
	_uv = NULL;
	_normal = NULL;
}
