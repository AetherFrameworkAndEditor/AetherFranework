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
		@brief          初期化用関数。派生先でオーバーライドし初期化の処理を記述
		@param          none
		@return         none
		@exception      none
		*/
		bool InitializeBuffers()override;

		/*
		@brief          解放用関数。派生先でオーバーライドし解放の処理を記述
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeBuffers()override;

		/*
		@brief          描画用関数。派生先でオーバーライドし描画の処理を記述
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