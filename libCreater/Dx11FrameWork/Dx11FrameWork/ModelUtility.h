#ifndef _MODELUTILITY_H
#define _MODELUTILITY_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      ModelUtility.h
@brief     ���f���Ƃ��Ɏg���悤�Ȋ֐��Q

*******************************************************************************
@date       2016/1/7 5:10
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/1/7 5:10 ���q�a��
-# Initial Version
- 2016/1/12 10:34 ���{�q
-# ��d��`�h�~��static�Ȋ֐��ɕύX
******************************************************************************/
#include"Direct3DManager.h"

namespace aetherFunction{

	static D3D11_BUFFER_DESC GetConstantBufferDesc(size_t strideType){
		D3D11_BUFFER_DESC desc = { strideType, D3D11_USAGE_DYNAMIC, D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, 0, 0 };
		return desc;
	}
};

#endif // !_MODELUTILITY_H