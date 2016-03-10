/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameActor.h
@brief     オブジェクト作成用基底クラス

*******************************************************************************
@date       2016/02/01 24:55
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/02/01 24:55 橋本航
-# Initial Version
******************************************************************************/
#ifndef _GAMEACTOR_H
#define _GAMEACTOR_H
#include <string>
#include <vector>
#include "FbxModel.h"
#include "ModelBase.h"
#include "ShaderBase.h"
#include "Cube.h"
#include "Sphere.h"
#include "Texture.h"
#include"Property.h"

namespace aetherClass{
	class GameActor
	{
	public:
		GameActor();
		virtual ~GameActor();

		/*
		@brief          FBXモデルを作成
		@param[in]		パス名
		@param[in]      軸
		@return         none
		@exception      none
		*/
		bool LoadFBX(std::string, eAxisSystem);

		/*
		@brief          FBXモデルのテクスチャのディレクトリの設定
		@param[in]		ディレクトリ名
		@return         none
		@exception      none
		*/
		void SetFbxTextureDirectory(std::string);


		/*
		@brief          基本モデルにテクスチャを設定
		@param[in]		Texture*
		@return         none
		@exception      none
		*/
		void SetTexture(Texture*);

		/*
		@brief          基本モデルの作成用
		@param[in]      ModelBaseを継承したオブジェクト
		@return         none
		@exception      none
		*/
		template<class ModelType>
		bool CreateModel(); 

		/*
		@brief          作成されたオブジェクト全てを描画する
		@param[in]      ShaderBase*
		@return         none
		@exception      none
		*/
		void Render(ShaderBase*, bool collideRender = false);

		/*
		@brief          キューブのコライダー作成用
		@param[in]      Cube*
		@return         none
		@exception      none
		*/
		void AddCollideObject(Cube*);

		/*
		@brief          球のコライダー作成用
		@param[in]      Sphere*
		@return         none
		@exception      none
		*/
		void AddCollideObject(Sphere*);

		/*
		@brief          好きな名前を設定できる
		@param[in]      std::string
		@return         none
		@exception      none
		*/
		void SetName(const std::string);

		/*
		@brief          名前の取得用
		@param[in]      none
		@return         std::string
		@exception      none
		*/
		std::string GetName()const;

		/*
		@brief          当たり判定を行うかを決める
		@param[in]      bool
		@return         none
		@exception      none
		*/
		void SetIsCollide(const bool);

		/*
		@brief          フラグ取得用
		@param[in]      none
		@return         bool
		@exception      none
		*/
		bool GetIsCollide()const;

		/*
		@brief          キューブコライド取得用
		@param[in]      none
		@return         bool
		@exception      none
		*/
		std::vector<Cube*> GetBoxCollide();

		/*
		@brief          球コライド取得用
		@param[in]      none
		@return         bool
		@exception      none
		*/
		std::vector<Sphere*> GetSphereCollide();

		/*
		@brief          カメラセット用
		@param[in]      ViewCamera*
		@return         none
		@exception      none
		*/
		void SetCamera(ViewCamera*);


		/*
		@brief          初期化用
		@param[in]      none
		@return         none
		@exception      none
		*/
		virtual bool Initialize();

		/*
		@brief          更新用
		@param[in]      none
		@return         none
		@exception      none
		*/
		virtual void Update() = 0;

		/*
		@brief          衝突判定時に行われる動作
		@param[in]      none
		@return         none
		@exception      none
		*/
		virtual void DoCollide();

		/*
		@brief          解放用
		@param[in]      none
		@return         none
		@exception      none
		*/
		virtual void Finlize();

		public:
			Property property;
	private:
		FbxModel* m_fbx;
		ModelBase* m_model;
		std::vector<Cube*> m_boxCollide;
		std::vector<Sphere*> m_sphereCollide;
		std::string m_objectName;
		bool m_isCollide;
		Vector3 m_prevPosition;
	};
}
#endif