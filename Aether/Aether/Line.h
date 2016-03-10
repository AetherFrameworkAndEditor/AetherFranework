#ifndef _LINE_H
#define _LINE_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Line.h
@brief     ���̊�{���f��

*******************************************************************************
@date       2016/1/15 11:23
@author     ���q�a��
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/1/15 11:23 ���q�a��
-# Initial Version

******************************************************************************/
#include "ModelBase.h"
#include"VertexType.h"

namespace aetherClass{
	struct RayVector
	{
		RayVector(){
			_origin = 0;
			_direction = 0;
			_scaler = 0;
		};
		Vector3 _origin;
		Vector3 _direction;
		float	_scaler;
	};

	class Line :
		public ModelBase
	{
	private:
		RayVector m_rayVector;
	public:
		Line();
		Line(RayVector);
		Line(Vector3, float);
		~Line();
	private:
		/*
		@brief          �������p�֐��B�h����ŃI�[�o�[���C�h���������̏������L�q
		@param          none
		@return         none
		@exception      none
		*/
		bool InitializeBuffers()override;

		/*
		@brief          ����p�֐��B�h����ŃI�[�o�[���C�h������̏������L�q
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeBuffers()override;

		/*
		@brief          �`��p�֐��B�h����ŃI�[�o�[���C�h���`��̏������L�q
		@param          none
		@return         none
		@exception      none
		*/
		void RenderBuffers()override;

	};

}
#endif