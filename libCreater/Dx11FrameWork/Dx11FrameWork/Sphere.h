#pragma once
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

	private:
		UINT m_sliceCount;
		UINT m_stackCount;
		float m_radius;
	};
}