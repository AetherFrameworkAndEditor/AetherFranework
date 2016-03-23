/******************************************************************************/
/*! @addtogroup aetherClass
@file      Particle.h
@brief     パーティクルクラス

*******************************************************************************
@date       2016/02/26
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/02/26 2:21 19:23 橋本航
-# Initial Version
******************************************************************************/
#ifndef _PARTICLE_H
#define _PARTICLE_H
#include "DirectXEntity.h"
#include <vector>
#include <string>
#include "ModelBase.h"
#include "SpriteBase.h"
#include "ShaderBase.h"
#include "Vector3.h"
namespace aetherClass{
	namespace{
		const int kDefaultCount = 100;
	}

	class Particle :
		DirectXEntity
	{
	
	public:
		/*
		@brief          パーティクルの描画モードの列挙型
		*/
		enum class eMode{
			eUnknown = 0,
			e2D,
			e3D,
			
		};
	public:
		Particle();
		~Particle();
		
		/*
		@brief          初期化用関数
		@param[in]      描画モードの設定(まだ3Dのみ)
		@param[in]      テクスチャのパス設定
		@param[in]      パーティクルの数の設定。デフォルトで100に設定
		@return         成功時：true/失敗時：false
		@exception      none
		*/
		bool Initialize(eMode renderMode, std::string texturePath, const int maxCount = kDefaultCount);

		/*
		@brief          解放用関数
		@param          none
		@return         none
		@exception      none
		*/
		void Finalize();

		/*
		@brief          描画用
		@param[in]      任意のシェーダーオブジェクト
		@return         none
		@exception      none
		*/
		void Render(ShaderBase*);

		/*
		@brief          更新用
		@param[in]      パーティクルの向き
		@param[in]      パーティクルの動きのスピード
		@return         none
		@exception      none
		*/
		void Update(Vector3 vector,float speed);

		/*
		@brief          消えるまでの長さを設定
		@param[in]      長さ
		@return         none
		@exception      none
		*/
		void SetActiveLength(const float);

		/*
		@brief          スケールの設定
		@param[in]      スケール値
		@return         none
		@exception      none
		*/
		void SetScale(Vector3);

		/*
		@brief          3Dパーティクルの時には必ず設定
		@param[in]      カメラオブジェクト
		@return         none
		@exception      none
		*/
		void SetCamera(ViewCamera*);

		/*
		@brief          パーティクルの出現範囲を設定できる
		@param[in]      範囲の最小値
		@param[in]      範囲の最大値
		@return         none
		@exception      none
		*/
		void SetRange(Vector3 min, Vector3 max);

		/*
		@brief          パーティクルの位置の設定
		@param[in]      初位置の設定
		@return         none
		@exception      none
		*/
		void SetPosition(Vector3);
	private:

		/*
		@brief          パーティクルのプロパティの初期化用
		@param          none
		@return         成功時：true/失敗時：false
		@exception      none
		*/
		bool InitializeParticle();

		/*
		@brief          2Dパーティクルの作成
		@param          none
		@return         成功時：true/失敗時：false
		@exception      none
		*/
		bool Create2DParticle(std::string texturePath, const int maxCount);

		/*
		@brief          2Dパーティクルの解放
		@param          none
		@return         none
		@exception      none
		*/
		void Remove2DParticle();

		/*
		@brief          2Dパーティクルの描画
		@param[in]      使用するシェーダーのポインタ
		@return         none
		@exception      none
		*/
		void Render2DParticle(ShaderBase*);

		/*
		@brief          2Dパーティクルの更新処理
		@param[in]      位置情報
		@param[in]      パーティクルの速度
		@return         none
		@exception      none
		*/
		void Update2DParticle(Vector3 position,float frameTime);

		/*
		@brief          2Dパーティクルの生成処理
		@param[in]      パーティクルの速度
		@return         none
		@exception      none
		*/
		void Emit2DParticles(float frameTime);

		/*
		@brief          2Dパーティクルの一部破棄処理
		@param          none
		@return         none
		@exception      none
		*/
		void Kill2DParticle();

		/*
		@brief          3Dパーティクル作成用
		@param          none
		@return         成功時：true/失敗時：false
		@exception      none
		*/
		bool Create3DParticle(std::string texturePath, const int maxCount);

		/*
		@brief          3Dパーティクルの解放用
		@param          none
		@return         none
		@exception      none
		*/
		void Remove3DParticle();

		/*
		@brief          3Dパーティクルの描画用
		@param[in]      シェーダーオブジェクト
		@return         none
		@exception      none
		*/
		void Render3DParticle(ShaderBase*);

		/*
		@brief          3Dパーティクルの更新用
		@param[in]      向き
		@param[in]      更新時間
		@return         none
		@exception      none
		*/
		void Update3DParticle(Vector3,float);

		/*
		@brief          3Dパーティクルの生成用
		@param[in]      更新時間
		@return         none
		@exception      none
		*/
		void Emit3DParticles(float frameTime);

		/*
		@brief          3Dパーティクルの調整用
		@param          none
		@return         none
		@exception      none
		*/
		void Kill3DParticle();
	private:
		/*
		@brief     2Dパーティクル用構造体
		*/
		struct Particle2D{
			aetherClass::SpriteBase* _sprite;
			float _velocity;
			bool _active;
		};

		/*
		@brief     3Dパーティクル用構造体
		*/
		struct Particle3D{
			aetherClass::ModelBase* _sprite;
			float _velocity;
			bool _active;
		};

	private:
		Vector3 m_particleDeviation, m_direction;
		Vector3 m_particlePosition;
		float m_particleVelocity, m_particleVelocityVariation;
		float m_particlesPerSecond;
		int m_currentParticleCount,m_maxParticle;
		float m_accumulatedTime;
		float m_maxActiveLength;

		std::vector<Particle3D> m_3dParticle;
		std::vector<Particle2D> m_2dParticle;
		eMode m_renderMode;
		Vector3 m_maxRange, m_minRange;
	};

}

#endif