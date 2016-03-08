#ifndef _MODELUTILITY_H
#define _MODELUTILITY_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      ModelUtility.h
@brief     モデルとかに使うような関数群

*******************************************************************************
@date       2016/1/7 5:10
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/1/7 5:10 金子和樹
-# Initial Version
- 2016/1/12 10:34 橋本航
-# 二重定義防止にstaticな関数に変更
******************************************************************************/
#include"Direct3DManager.h"

namespace aetherFunction{

	static D3D11_BUFFER_DESC GetConstantBufferDesc(size_t strideType){
		D3D11_BUFFER_DESC desc = { strideType, D3D11_USAGE_DYNAMIC, D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, 0, 0 };
		return desc;
	}
};

#endif // !_MODELUTILITY_H
