/******************************************************************************/
/*! @addtogroup aetherClass
@file      ModelBase.h
@brief     モデルクラスの基底クラス

*******************************************************************************
@date       2016/01/05 1:29
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/1/5 1:29 橋本航
-# Initial Version
- 2016/1/7 4:37	金子和樹
-#　色々な更新Color Tranform Material 追加
- 2016/1/10 18:17 金子和樹
-#　シェーダー開放
- 2016/1/20 21:08
-#　MaterialをConstant bufferへ登録
******************************************************************************/

#ifndef _MODELBASE_H
#define _MODELBASE_H
#include <string>
#include <memory>

#include "Direct3DManager.h"
#include "DirectXEntity.h"
#include "Axis.h"
#include "Texture.h"
#include"ViewCamera.h"
#include"ShaderBase.h"
#include"Property.h"

namespace aetherClass{
	class ModelBase : 
		public DirectXEntity
	{
	
	public:
		ModelBase();
		virtual ~ModelBase()=default;

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
		@brief          描画時に適用するカメラのアドレスを取得。これが呼ばれないと、正常な描画ができない。
		@param[in]      ViewCamera型のポインタアドレス
		@return         none
		@exception      none
		*/
		virtual void SetCamera(ViewCamera*)final;

		/*
		@brief          インデックス数の取得
		@param[in]      none
		@return         インデックス数
		@exception      none
		*/
		virtual int GetIndexCount()final;


		/*
		@brief          Axis型の参照を得る
		@param[in]      none
		@return         Axis型変数への参照
		@exception      none
		*/
		virtual Axis& GetAxis()final;

		virtual std::string GetName()const;

	public:
		Property property;
	protected:
		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer, *m_colorBuffer, *m_materialBuffer;;
		unsigned long m_vertexCount, m_indexCount;

		Texture* m_texture;
		ViewCamera* m_camera;

	protected:
		virtual void SetName(const std::string);

	private:
	
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

	private:
		Axis m_axis;
		std::string m_modelName;
	
	};
}
#endif