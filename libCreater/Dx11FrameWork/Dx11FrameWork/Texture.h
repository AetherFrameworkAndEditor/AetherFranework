/******************************************************************************/
/*! @addtogroup aetherClass
@file      Texture.h
@brief     �e�N�X�`���Ǘ��N���X
*******************************************************************************
@date       2015/12/27
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/27 ���{�q
-# Initial Version
- 2016/01/12 10:10 ���{�q
-# Finalize��private�����o�ɕύX�B
- 2016/01/20 17:03 ���{�q
-# SamplerState�I�u�W�F�N�g�̒ǉ��B����ɔ���Getter�̒ǉ��B
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
		@brief          �e�N�X�`���̏������B
		@param[in]      ID3D11Device�̃I�u�W�F�N�g
		@param[in]      �摜�̑��΃p�X
		@return         ������ ture/���s�� false
		@exception      none
		*/
		bool Load(std::string);

		/*
		@brief          Load�֐��ō쐬�����e�N�X�`���擾�p�B
		@param[in]      none
		@return         ID3D11ShaderResourceView*
		@exception      none
		*/
		ID3D11ShaderResourceView* GetTexture();

		/*
		@brief          �T���v���[�X�e�[�g�擾�B
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