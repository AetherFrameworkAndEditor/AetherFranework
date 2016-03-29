/******************************************************************************/
/*! @addtogroup aetherClass
@file      WorldReader.h
@brief     �Ǝ��`���t�@�C���ǂݍ��ݗp�N���X�B�G�f�B�^�[�Ƃ̘A�g�p

*******************************************************************************
@date       2016/3/7
@author     ���؍q
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/
#ifndef _WORLDREADER_H
#define _WORLDREADER_H
#include <string>
#include "World.h"
class WorldReader
{
public:
	WorldReader();
	~WorldReader();

	/*
	@brief          Editor�ō쐬���ꂽ�Ǝ��t�@�C���̓ǂݍ���(�ǂݍ��߂�t�@�C���F*.aether)
	@param[in]      �t�@�C�����B
	@return         ���������@true/���s false
	*/
	bool Load(std::string);

	/*
	@brief          Load�œǂݎ���������������߂̊֐�
	@param[out]     World�\���̕ϐ�    
	@return			none
	*/
	World GetInputWorldInfo();

	/*
	@brief          �ǂݍ��񂾏�񂷂ׂĂ̔j���p
	@param          none
	@return			none
	*/
	void UnLoad();

	/*
	@brief          �ǂݍ��񂾃e�N�X�`�����̔j���p
	@param          none
	@return			none
	*/
	void UnLoadTexture();

	/*
	@brief          �ǂݍ��񂾃I�u�W�F�N�g���̔j���p
	@param          none
	@return			none
	*/
	void UnLoadObject();

	/*
	@brief          �ǂݍ��񂾃}�e���A�����̔j���p
	@param          none
	@return			none
	*/
	void UnLoadMaterial();
private:
	World m_world;
	std::vector<std::string> m_input;
	std::string m_tag;
private:
	std::string GetExtension(const std::string path);
	void GetObjectInfo(std::string);
	void GetMaterialInfo(std::string);
	void GetCameraInfo(std::string);
	void GetTextureInfo(std::string);
	void GetLightInfo(std::string);
};

#endif