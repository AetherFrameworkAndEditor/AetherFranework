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
