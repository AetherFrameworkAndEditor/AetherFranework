#ifndef _VIEWCAMERA_H
#define _VIEWCAMERA_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      ViewCamera.h
@brief     �J�����̃N���X

*******************************************************************************
@date       2016/1/7
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/
#define DEBUG_MODE
#include "Vector3.h"
#include"Matrix4x4.h"
#include "Direct3DManager.h"
namespace aetherClass{
	class ViewCamera
	{
	public:
		struct Property{
			Vector3 _translation;
			Vector3 _rotation;
			Vector3 _lookUp;
			Vector3 _lookAt;
		};
	public:
		ViewCamera();
		~ViewCamera() = default;

		Property property;

		/*
		@brief          �r���[�s��𐶐�����
		@param[in]      none
		@return         none
		@exception      none
		*/
		void Render();
		/*
		@brief          �r���[�s����擾����
		@param[in]      none
		@return         �r���[�s��
		@exception      none
		*/
		Matrix4x4 GetViewMatrix();
#ifdef DEBUG_MODE
		/*
		@brief          �J�����R���g���[�����Ă�
		@param[in]      none
		@return         none
		@exception      DEBUG_MODE����`����Ă���Ύg�p�\
		*/
		void Controller();
#endif

	private:
		Matrix4x4 m_viewMatrix;
	};


}

#endif