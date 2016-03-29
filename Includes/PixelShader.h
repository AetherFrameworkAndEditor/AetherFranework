#ifndef _PIXELSHADER_H
#define _PIXELSHADER_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      PixelShader.h
@brief     基本的なシェーダー。既に割り当てられた情報を扱うときに。

*******************************************************************************
@date       2016/1/10
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/

#include "ShaderBase.h"
namespace aetherClass{
	class  PixelShader :
		public ShaderBase
	{

	
	public:
		PixelShader();
		~PixelShader() = default;

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
	};


}

#endif