/******************************************************************************/
/*! @addtogroup aetherClass
@file      Texture.h
@brief     テクスチャ管理クラス
*******************************************************************************
@date       2015/12/27
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/27 橋本航
-# Initial Version
- 2016/01/12 10:10 橋本航
-# Finalizeをprivateメンバに変更。
- 2016/01/20 17:03 橋本航
-# SamplerStateオブジェクトの追加。それに伴うGetterの追加。
******************************************************************************/
#ifndef _TEXTURE_H
#define _TEXTURE_H
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#include <d3d11.h>
#include <string>
#include "DirectXEntity.h"
namespace aetherClass{
	class Texture:
		aetherClass::DirectXEntity
	{
	public:
		Texture();
		~Texture();

		/*
		@brief          テクスチャの初期化。
		@param[in]      ID3D11Deviceのオブジェクト
		@param[in]      画像の相対パス
		@return         成功時 ture/失敗時 false
		@exception      none
		*/
		bool Load(std::string);

		/*
		@brief          Load関数で作成したテクスチャ取得用。
		@param[in]      none
		@return         ID3D11ShaderResourceView*
		@exception      none
		*/
		ID3D11ShaderResourceView* GetTexture();

		/*
		@brief          サンプラーステート取得。
		@param[in]      none
		@return         ID3D11ShaderResourceView*
		@exception      none
		*/
		ID3D11SamplerState* GetSamplerState();

		std::string GetPath()const;

	private:
		std::string m_path;
		ID3D11ShaderResourceView* m_texture;
		ID3D11SamplerState *m_samplerState;
	private:
		void Release();
	};
}
#endif