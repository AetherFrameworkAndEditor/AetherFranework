/******************************************************************************/
/*! @addtogroup aetherClass
@file      FbxModel.h
@brief     Fbxモデルの基底クラス
　　　　　　基本的なモデルの描画もできる

*******************************************************************************
@date       2016/01/15
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _FBXMODEL_H
#define _FBXMODEL_H

#include <memory>
#include "ShaderBase.h"
#include "FbxLoader.h"
#include "DirectXEntity.h"
#include "Mesh.h"
#include "ViewCamera.h"
namespace aetherClass{

	

	class FbxModel:
		DirectXEntity
	{
	private:
		struct Property{
			Transform _transform;
		};
	public:
		 FbxModel::Property property;
	public:
		FbxModel();
		virtual ~FbxModel() = default;

		/*
		@brief          FbxFileの読み込みと初期化
		@param[in]      Shaderオブジェクト
		@return         none
		@exception      none
		*/
		virtual bool LoadFBX(std::string, eAxisSystem)final;

		/*
		@brief          解放用
		@param[in]      Shaderオブジェクト
		@return         none
		@exception      none
		*/
		virtual void Finalize()final;

		/*
		@brief          全てのノード描画用
		@param[in]      Shaderオブジェクト
		@return         none
		@exception      none
		*/
		virtual void Render(ShaderBase*)final;

		/*
		@brief          指定ノードのみ描画用。
		                範囲外の場合はすべてのノードを描画
		@param[in]      Shaderオブジェクト
		@param[in]      描画するノード番号（ 0以上の整数値 ）
		@return         none
		@exception      none
		*/
		virtual void NodeRender(ShaderBase*, const int id)final;


		/*
			キーフレームアニメーション用
		*/
		virtual void KeyFrameAnimation(ShaderBase* shader)final;

		/*
		キーフレームアニメーション用
		*/
	//	virtual void SkinAnimation(ShaderBase* shader)final;

		/*
		@brief          投影するカメラのアドレス取得用
		@param[in]      ViewCamera型オブジェクト
		@return         none
		@exception      none
		*/
		virtual void SetCamera(ViewCamera*)final;


		/*
		@brief          指定のノードを好きな色に設定できる
		ノード番号が範囲外の場合はすべてに対して変更
		@param[in]      rgba
		@param[in]      変更を反映したいノード番号（ 0以上の整数値 ）
		@return         none
		@exception      none
		*/
		virtual void SetModelMaterialColor(Color rgba, const int nodeID, eMatrerialType)final;

		/*
		@brief          全てのノードを好きな色に設定できる
		ノード番号が範囲外の場合はすべてに対して変更
		@param[in]      rgba
		@param[in]      変更を反映したいノード番号（ 0以上の整数値 ）
		@return         none
		@exception      none
		*/
		virtual void SetModelMaterialColor(Color rgba, eMatrerialType)final;

		/*
		@brief          指定のノードのテクスチャオブジェクトを取得
		@param[in]      指定ノード番号
		@return         ID3D11ShaderResourceView型オブジェクト
		@exception      none
		*/
		virtual ID3D11ShaderResourceView* GetTexture(const int id)final;

		
		/*
		@brief          全てのノードに対して同じテクスチャオブジェクトを取得
		@param          作成したいテクスチャ画像の相対パス
		@return         成功時：ture/失敗時:false
		@exception      none
		*/
		virtual bool SetTexture(Texture*,eMatrerialType)final;

		/*
		@brief          指定のノードに対して同じテクスチャを取得
		@param          作成したいテクスチャ画像の相対パス
		@param[in]      指定ノード番号
		@return         成功時：ture/失敗時:false
		@exception      none
		*/
		virtual bool SetNodeTexture(Texture*, const int id, eMatrerialType)final;

		/*
		@brief          テクスチャのある親ディレクトリーの設定.そして各テクスチャの読み込み
		@param[in]      ディレクトリー名の設定
		@return         成功時：ture/失敗時:false
		@exception      none
		*/
		virtual void SetTextureDirectoryName(std::string)final;

		virtual std::string GetModelPath()const final;
	protected:

		std::vector<Mesh> m_nodeMeshBuffer;
		std::unique_ptr<FbxLoader> m_fbxLoader;
		

	private:
		/*
		@brief          基本情報の取得
		@param[in]      Direct3DManager型のアドレス
		@return         成功時：ture/失敗時:false
		@exception      none
		*/
		virtual bool LoadModelBuffers(Direct3DManager*)final;

		/*
		@brief          ノードごとに読み取る情報の記述
		@param[in]      Direct3DManager型のアドレス
		@return         成功時：ture/失敗時:false
		@exception      none
		*/
		virtual bool LoadNodeMesh(){ return true; }

		/*
		@brief          描画処理
		@param[in]      Direct3DManager型のアドレス
		@param[in]      描画するノード番号
		@return         none
		@exception      none
		*/
		virtual void RenderBuffers(Direct3DManager*, Mesh)final;

		/*
		@brief          シェーダーに渡すパラメーターを設定する関数。派生先でオーバーライドし処理を記述
		@param          情報を得たのModelMesh型ポインタ
		@return         none
		@exception      none
		*/
		virtual void CreateConstantBuffers(Mesh);



	private:
		ViewCamera* m_camera;
		std::string m_modelPath;
	};

}

#endif