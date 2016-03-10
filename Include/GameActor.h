/******************************************************************************/
/*! @addtogroup aetherClass
@file      GameActor.h
@brief     �I�u�W�F�N�g�쐬�p���N���X

*******************************************************************************
@date       2016/02/01 24:55
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2016/02/01 24:55 ���{�q
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
		@brief          FBX���f�����쐬
		@param[in]		�p�X��
		@param[in]      ��
		@return         none
		@exception      none
		*/
		bool LoadFBX(std::string, eAxisSystem);

		/*
		@brief          FBX���f���̃e�N�X�`���̃f�B���N�g���̐ݒ�
		@param[in]		�f�B���N�g����
		@return         none
		@exception      none
		*/
		void SetFbxTextureDirectory(std::string);


		/*
		@brief          ��{���f���Ƀe�N�X�`����ݒ�
		@param[in]		Texture*
		@return         none
		@exception      none
		*/
		void SetTexture(Texture*);

		/*
		@brief          ��{���f���̍쐬�p
		@param[in]      ModelBase���p�������I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		template<class ModelType>
		bool CreateModel(); 

		/*
		@brief          �쐬���ꂽ�I�u�W�F�N�g�S�Ă�`�悷��
		@param[in]      ShaderBase*
		@return         none
		@exception      none
		*/
		void Render(ShaderBase*, bool collideRender = false);

		/*
		@brief          �L���[�u�̃R���C�_�[�쐬�p
		@param[in]      Cube*
		@return         none
		@exception      none
		*/
		void AddCollideObject(Cube*);

		/*
		@brief          ���̃R���C�_�[�쐬�p
		@param[in]      Sphere*
		@return         none
		@exception      none
		*/
		void AddCollideObject(Sphere*);

		/*
		@brief          �D���Ȗ��O��ݒ�ł���
		@param[in]      std::string
		@return         none
		@exception      none
		*/
		void SetName(const std::string);

		/*
		@brief          ���O�̎擾�p
		@param[in]      none
		@return         std::string
		@exception      none
		*/
		std::string GetName()const;

		/*
		@brief          �����蔻����s���������߂�
		@param[in]      bool
		@return         none
		@exception      none
		*/
		void SetIsCollide(const bool);

		/*
		@brief          �t���O�擾�p
		@param[in]      none
		@return         bool
		@exception      none
		*/
		bool GetIsCollide()const;

		/*
		@brief          �L���[�u�R���C�h�擾�p
		@param[in]      none
		@return         bool
		@exception      none
		*/
		std::vector<Cube*> GetBoxCollide();

		/*
		@brief          ���R���C�h�擾�p
		@param[in]      none
		@return         bool
		@exception      none
		*/
		std::vector<Sphere*> GetSphereCollide();

		/*
		@brief          �J�����Z�b�g�p
		@param[in]      ViewCamera*
		@return         none
		@exception      none
		*/
		void SetCamera(ViewCamera*);


		/*
		@brief          �������p
		@param[in]      none
		@return         none
		@exception      none
		*/
		virtual bool Initialize();

		/*
		@brief          �X�V�p
		@param[in]      none
		@return         none
		@exception      none
		*/
		virtual void Update() = 0;

		/*
		@brief          �Փ˔��莞�ɍs���铮��
		@param[in]      none
		@return         none
		@exception      none
		*/
		virtual void DoCollide();

		/*
		@brief          ����p
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