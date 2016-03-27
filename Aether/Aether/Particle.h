/******************************************************************************/
/*! @addtogroup aetherClass
@file      Particle.h
@brief     �p�[�e�B�N���N���X

*******************************************************************************
@date       2016/02/26
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/02/26 2:21 19:23 ���{�q
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
		@brief          �p�[�e�B�N���̕`�惂�[�h�̗񋓌^
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
		@brief          �������p�֐�
		@param[in]      �`�惂�[�h�̐ݒ�(�܂�3D�̂�)
		@param[in]      �e�N�X�`���̃p�X�ݒ�
		@param[in]      �p�[�e�B�N���̐��̐ݒ�B�f�t�H���g��100�ɐݒ�
		@return         �������Ftrue/���s���Ffalse
		@exception      none
		*/
		bool Initialize(eMode renderMode, std::string texturePath, const int maxCount = kDefaultCount);

		/*
		@brief          ����p�֐�
		@param          none
		@return         none
		@exception      none
		*/
		void Finalize();

		/*
		@brief          �`��p
		@param[in]      �C�ӂ̃V�F�[�_�[�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void Render(ShaderBase*);

		/*
		@brief          �X�V�p
		@param[in]      �p�[�e�B�N���̌���
		@param[in]      �p�[�e�B�N���̓����̃X�s�[�h
		@return         none
		@exception      none
		*/
		void Update(Vector3 vector,float speed);

		/*
		@brief          ������܂ł̒�����ݒ�
		@param[in]      ����
		@return         none
		@exception      none
		*/
		void SetActiveLength(const float);

		/*
		@brief          �X�P�[���̐ݒ�
		@param[in]      �X�P�[���l
		@return         none
		@exception      none
		*/
		void SetScale(Vector3);

		/*
		@brief          3D�p�[�e�B�N���̎��ɂ͕K���ݒ�
		@param[in]      �J�����I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void SetCamera(ViewCamera*);

		/*
		@brief          �p�[�e�B�N���̏o���͈͂�ݒ�ł���
		@param[in]      �͈͂̍ŏ��l
		@param[in]      �͈͂̍ő�l
		@return         none
		@exception      none
		*/
		void SetRange(Vector3 min, Vector3 max);

		/*
		@brief          �p�[�e�B�N���̈ʒu�̐ݒ�
		@param[in]      ���ʒu�̐ݒ�
		@return         none
		@exception      none
		*/
		void SetPosition(Vector3);
	private:

		/*
		@brief          �p�[�e�B�N���̃v���p�e�B�̏������p
		@param          none
		@return         �������Ftrue/���s���Ffalse
		@exception      none
		*/
		bool InitializeParticle();

		/*
		@brief          2D�p�[�e�B�N���̍쐬
		@param          none
		@return         �������Ftrue/���s���Ffalse
		@exception      none
		*/
		bool Create2DParticle(std::string texturePath, const int maxCount);

		/*
		@brief          2D�p�[�e�B�N���̉��
		@param          none
		@return         none
		@exception      none
		*/
		void Remove2DParticle();

		/*
		@brief          2D�p�[�e�B�N���̕`��
		@param[in]      �g�p����V�F�[�_�[�̃|�C���^
		@return         none
		@exception      none
		*/
		void Render2DParticle(ShaderBase*);

		/*
		@brief          2D�p�[�e�B�N���̍X�V����
		@param[in]      �ʒu���
		@param[in]      �p�[�e�B�N���̑��x
		@return         none
		@exception      none
		*/
		void Update2DParticle(Vector3 position,float frameTime);

		/*
		@brief          2D�p�[�e�B�N���̐�������
		@param[in]      �p�[�e�B�N���̑��x
		@return         none
		@exception      none
		*/
		void Emit2DParticles(float frameTime);

		/*
		@brief          2D�p�[�e�B�N���̈ꕔ�j������
		@param          none
		@return         none
		@exception      none
		*/
		void Kill2DParticle();

		/*
		@brief          3D�p�[�e�B�N���쐬�p
		@param          none
		@return         �������Ftrue/���s���Ffalse
		@exception      none
		*/
		bool Create3DParticle(std::string texturePath, const int maxCount);

		/*
		@brief          3D�p�[�e�B�N���̉���p
		@param          none
		@return         none
		@exception      none
		*/
		void Remove3DParticle();

		/*
		@brief          3D�p�[�e�B�N���̕`��p
		@param[in]      �V�F�[�_�[�I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void Render3DParticle(ShaderBase*);

		/*
		@brief          3D�p�[�e�B�N���̍X�V�p
		@param[in]      ����
		@param[in]      �X�V����
		@return         none
		@exception      none
		*/
		void Update3DParticle(Vector3,float);

		/*
		@brief          3D�p�[�e�B�N���̐����p
		@param[in]      �X�V����
		@return         none
		@exception      none
		*/
		void Emit3DParticles(float frameTime);

		/*
		@brief          3D�p�[�e�B�N���̒����p
		@param          none
		@return         none
		@exception      none
		*/
		void Kill3DParticle();
	private:
		/*
		@brief     2D�p�[�e�B�N���p�\����
		*/
		struct Particle2D{
			aetherClass::SpriteBase* _sprite;
			float _velocity;
			bool _active;
		};

		/*
		@brief     3D�p�[�e�B�N���p�\����
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