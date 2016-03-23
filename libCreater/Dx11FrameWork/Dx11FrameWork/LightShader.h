#ifndef _LIGHTSHADER_H
#define _LIGHTSHADER_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      LightShader.h
@brief     ライトを扱うシェーダークラス

*******************************************************************************
@date       2016/1/19
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/

#include "ShaderBase.h"
#include"ModelUtility.h"
#include"Light.h"

namespace aetherClass{
	class LightShader :
		public ShaderBase
	{
	public:
		LightShader();
		~LightShader();

		/*
		@brief          ライトを設定する
		@param          ライトオブジェクト
		@return         none
		@exception      none
		*/
		void SetLight(Light*);
	private:
		/*
		@brief          初期化用関数
		@param          none
		@return         true/false
		@exception      none
		*/
		bool InitializeShader()override;
		/*
		@brief          終了用関数
		@param          none
		@return         none
		@exception      none
		*/
		void FinalizeShader()override;
		/*
		@brief          描画時用関数
		@param          none
		@return         true/false
		@exception      none
		*/
		bool SetConstantBuffer()override;

		ID3D11Buffer* m_lightBuffer;
		Light *m_light;
	};
}

#endif