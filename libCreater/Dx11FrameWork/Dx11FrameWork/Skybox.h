#ifndef _SKYBOX_H
#define _SKYBOX_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Skybox.h
@brief     スカイボックスのクラス

*******************************************************************************
@date       2016/2/24
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************/
#include "ModelBase.h"
#include"VertexType.h"

namespace aetherClass{
	class Skybox :
		public ModelBase
	{
	public:
		Skybox();
		~Skybox();
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

		/*
		@brief          シェーダーに渡すパラメーターを設定する関数。派生先でオーバーライドし処理を記述
		@param          none
		@return         none
		@exception      none
		*/
		void CreateConstantBuffers()override;
		ID3D11SamplerState *m_samplerState;
	};

}
#endif