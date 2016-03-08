/******************************************************************************/
/*! @addtogroup aetherClass
@file      ModelBase.h
@brief     モデルクラスの基底クラス

*******************************************************************************
@date       2016/01/05 1:29
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/1/5 1:21 金子和樹
-# Initial Version

******************************************************************************/

#ifndef _SPRITEBASE_H
#define _SPRITEBASE_H
#include "DirectXEntity.h"
#include "Transform.h"
#include "Axis.h"
#include "Texture.h"
#include"Material.h"
#include"ShaderBase.h"
namespace aetherClass{
	class SpriteBase :
		public DirectXEntity
	{
	private:
		struct Property
		{
			Transform _transform;
			Color _color;
		};
	public:
		SpriteBase();
		virtual ~SpriteBase() = default;


		/*
		@brief          テクスチャのアドレスを受け渡す用。
		@param[in]      Texture型オブジェクト
		@return         成功時 ture/失敗時 false
		@exception      none
		*/
		virtual void SetTexture(Texture*) final;

		/*
		@brief          解放処理用関数。必ず呼ぶ
		@param[in]      テクスチャのパス名
		@return         成功時 ture/失敗時 false
		@exception      none
		*/
		virtual void Finalize() final;

		/*
		@brief          初期化用関数。必ず呼ぶ
		@param          none
		@return         成功時 ture/失敗時 false
		@exception      none
		*/
		virtual bool Initialize()final;

		/*
		@brief          描画用関数。必ず呼ぶ。
		@param[in]      テクスチャのパス名
		@return         none
		@exception      none
		*/
		virtual void Render(ShaderBase*)final;



		/*
		@brief          インデックス数の取得
		@param[in]      none
		@return         インデックス数
		@exception      none
		*/
		virtual int GetIndexCount()final;
		
	private :
		/*
		@brief          初期化用関数。派生先でオーバーライドし初期化の処理を記述
		@param          none
		@return         none
		@exception      none
		*/
		virtual bool InitializeBuffers() = 0;

		/*
		@brief          解放用関数。派生先でオーバーライドし解放の処理を記述
		@param          none
		@return         none
		@exception      none
		*/
		virtual void FinalizeBuffers() = 0;

		/*
		@brief          描画用関数。派生先でオーバーライドし描画の処理を記述
		@param          none
		@return         none
		@exception      none
		*/
		virtual void RenderBuffers() = 0;

		/*
		@brief          シェーダーに渡すパラメーターを設定する関数。派生先でオーバーライドし処理を記述
		@param          none
		@return         none
		@exception      none
		*/
		virtual void CreateConstantBuffers();
	public:
		Property property;
	protected:
		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer, *m_colorBuffer;
		unsigned long m_vertexCount, m_indexCount;

		Texture* m_texture;


	};
}
#endif