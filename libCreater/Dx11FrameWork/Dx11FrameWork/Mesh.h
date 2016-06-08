/******************************************************************************/
/*! @addtogroup aetherClass
@file      Mesh.h
@brief     ���b�V�����Ǘ��N���X
*******************************************************************************
@date       2015/12/27
@author     ���{�q
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
		@brief          SetTexture�œǂݍ��܂ꂽ�e�N�X�`���̎擾
		@param[in]      none
		@return         ID3D11ShaderResourceView�̃|�C���^
		@exception      none
		*/
		ID3D11ShaderResourceView* GetTexture();

		/*
		@brief          SetTexture�œǂݍ��܂ꂽ�T���v���[�X�e�[�g�̎擾
		@param[in]      none
		@return         ID3D11ShaderResourceView�̃|�C���^
		@exception      none
		*/
		ID3D11SamplerState* GetSamplerState();

		/*
		@brief          �쐬�ς݂̃e�N�X�`���̎擾
		@param[in]      �e�N�X�`���I�u�W�F�N�g
		@return         none
		@exception      none
		*/
		void SetTexture(Texture*);

		/*
		@brief          �e�N�X�`���[�N���X�I�u�W�F�N�g�̃����������݂��Ă��邩�m�F�p
		@param          none
		@return         ���݂���Ftrue/���݂��Ȃ�:false
		@exception      none
		*/
		bool IsTextureVisible(); 

		/*
		@brief          ���̃N���X�������ׂĂ̏������S�ɉ���܂��͏�����
		@param          none
		@return         none
		@exception      none
		*/
		void Release();
	private:
		Texture* _texture;

	private:

		/*
		@brief          ID3D11Buffer�n�̕ϐ��j���p
		@param          none
		@return         none
		@exception      none
		*/
		void ReleaseBuffer();


		/*
		@brief		    �ڍ׏��S��NULL�܂���nullptr�ŏ�����
		@param          none
		@return         none
		@exception      none
		*/
		void ResetProperty();

	
		
	};
}
#endif