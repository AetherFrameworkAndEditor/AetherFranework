/******************************************************************************/
/*! @addtogroup aetherClass
@file      Mesh.h
@brief     メッシュ情報管理クラス
*******************************************************************************
@date       2015/12/27
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _NODEMESH_H
#define _NODEMESH_H
#include <memory>
#include "Direct3DManager.h"
#include "Material.h"
#include "Texture.h"
#include "Color.h"
#include "Transform.h"
#include "Axis.h"
#include "Matrix4x4.h"
#include "DirectXEntity.h"
#include "Property.h"
namespace aetherClass{


	class Mesh:
		DirectXEntity
	{
	public:
		ID3D11Buffer* _vertexBuffer;
		ID3D11Buffer* _indexBuffer;
		ID3D11Buffer* _colorBuffer;
		ID3D11Buffer* _materialBuffer;

		Property property;
		Matrix4x4 _meshMatrix; 
		std::unordered_map<std::string, std::vector<Transform>> _animationTransform;
		
		unsigned long _vertexCount, _indexCount;

	public:
		Mesh();
		~Mesh();

		/*
		@brief          SetTextureで読み込まれたテクスチャの取得
		@param[in]      none
		@return         ID3D11ShaderResourceViewのポインタ
		@exception      none
		*/
		ID3D11ShaderResourceView* GetTexture();

		/*
		@brief          SetTextureで読み込まれたサンプラーステートの取得
		@param[in]      none
		@return         ID3D11ShaderResourceViewのポインタ
		@exception      none
		*/
		ID3D11SamplerState* GetSamplerState();

		/*
		@brief          作成済みのテクスチャの取得
		@param[in]      テクスチャオブジェクト
		@return         none
		@exception      none
		*/
		void SetTexture(Texture*);

		/*
		@brief          テクスチャークラスオブジェクトのメモリが存在しているか確認用
		@param          none
		@return         存在する：true/存在しない:false
		@exception      none
		*/
		bool IsTextureVisible(); 

		/*
		@brief          このクラスが持つすべての情報を安全に解放または初期化
		@param          none
		@return         none
		@exception      none
		*/
		void Release();
	private:
		Texture* _texture;

	private:

		/*
		@brief          ID3D11Buffer系の変数破棄用
		@param          none
		@return         none
		@exception      none
		*/
		void ReleaseBuffer();


		/*
		@brief		    詳細情報全てNULLまたはnullptrで初期化
		@param          none
		@return         none
		@exception      none
		*/
		void ResetProperty();

	
		
	};
}
#endif