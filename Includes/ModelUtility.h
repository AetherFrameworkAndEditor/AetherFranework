#ifndef _MODELUTILITY_H
#define _MODELUTILITY_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      ModelUtility.h
@brief     ���f���Ƃ��Ɏg���悤�Ȋ֐��Q

*******************************************************************************
@date       2016/1/7
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#include"Direct3DManager.h"
namespace aetherFunction{

	/*
	@brief          �R���X�^���o�b�t�@�����������鎞�p
	@param[in]      �o�b�t�@�T�C�Y
	@return         BufferDesc
	@exception      none
	*/
	static D3D11_BUFFER_DESC GetConstantBufferDesc(size_t strideType){
		D3D11_BUFFER_DESC desc = { strideType, D3D11_USAGE_DYNAMIC, D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, 0, 0 };
		return desc;
	}
	/*
	@brief          �E�B���h�E�T�C�Y�𓾂�
	@param[in]      �E�B���h�E�n���h��
	@return         �E�B���h�E�T�C�Y
	@exception      none
	*/
	static aetherClass::Vector2 GetWindowSize(HWND hWnd){
		RECT screen;
		GetWindowRect(hWnd, &screen);
		aetherClass::Vector2 screenSize = { float(screen.right - screen.left - GetSystemMetrics(SM_CXDLGFRAME) * 2),
			float(screen.bottom - screen.top - GetSystemMetrics(SM_CXDLGFRAME) * 2) };
		return screenSize;
	}
};

#endif // !_MODELUTILITY_H
