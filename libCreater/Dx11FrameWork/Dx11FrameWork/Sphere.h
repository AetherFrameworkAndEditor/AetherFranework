/******************************************************************************/
/*! @addtogroup aetherClass
@file      Sphere.h
@brief     球作成用クラス

*******************************************************************************
@date       2016/01/05
@author     湯川計
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
		@brief          基底クラスから呼ばれる
		@param          none
		@return         none
		@exception      none
		*/
		bool InitializeBuffers()override;

		/*
		@brief          基底クラスから呼ばれる
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeBuffers()override;

		/*
		@brief          基底クラスから呼ばれる
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