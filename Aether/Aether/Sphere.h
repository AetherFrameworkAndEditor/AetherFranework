/******************************************************************************/
/*! @addtogroup aetherClass
@file      Sphere.h
@brief     ���쐬�p�N���X

*******************************************************************************
@date       2016/01/05
@author     ����v
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/
#ifndef _SPHERE_H
#define _SPHERE_H
#include "ModelBase.h"
#include "VertexType.h"
namespace aetherClass
{
	class Sphere :
		public ModelBase
	{
	public:
		Sphere(UINT,UINT);
		~Sphere();

	private:
		/*
		@brief          ���N���X����Ă΂��
		@param          none
		@return         none
		@exception      none
		*/
		bool InitializeBuffers()override;

		/*
		@brief          ���N���X����Ă΂��
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeBuffers()override;

		/*
		@brief          ���N���X����Ă΂��
		@param          none
		@return         none
		@exception      none
		*/
		void RenderBuffers()override;

	private:
		UINT m_sliceCount;
		UINT m_stackCount;
		float m_radius;
	};
}
#endif