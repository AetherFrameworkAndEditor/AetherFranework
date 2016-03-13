/******************************************************************************/
/*! @addtogroup aetherClass
@file      Material.h
@brief     �}�e���A���̃p�����[�^�[��ێ�����ϐ�������N���X

*******************************************************************************
@date       2015/12/27
@author    ���q �a��
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/27 ���q �a��
-# Initial Version
- 2015/12/27 ���{ �q
-# �V�����݌v�ɍ��킹��
- 2015/12/27 ���{ �q
-# delete GetMaterial function
- 2015/12/27 ���{ �q
-# add MaterialElement struct
******************************************************************************/
#ifndef _MATERIAL_H
#define _MATERIAL_H
#include <vector>
#include"Vector4.h"
#include"Vector3.h"
#include"Texture.h"
namespace aetherClass{
	
	// �}�e���A���̗v�f�\����
	struct MaterialElement{
		enum class eMaterialElementType{
			eElementNone = 0,
			eElementColor,
			eElementTexture,
			eElementBoth,
			eElementMax
		};

		// UVSet���ƃe�N�X�`���̃p�X��.1��UVSet���ɑ΂��ăe�N�X�`������������ꍇ������
		Texture* _texture;
		std::vector<std::string> _texturePath;
		eMaterialElementType _type;
		Color _color;
	};

	struct MaterialBufferType
	{
		Color _diffuse;
		Color _specular;
		Color _ambient;
		Color _emissive;
		float _specularPower;
		float _shininess;
		float _transparencyFactor;
		float Padding;
	};

	enum class eMatrerialType{
		eAmbient,
		eSpecular,
		eDiffuse,
		eEmissive,
	};

	class Material
	{
	public:
		Material();
		~Material();

		// FBX�̃}�e���A���͓��ނ����Ȃ�
		enum class eFbxMaterialType{
			eMaterialLambert = 0,
			eMaterialPhong
		};

		eFbxMaterialType _type;

		MaterialElement _ambient;
		MaterialElement _specular;
		MaterialElement _diffuse;
		MaterialElement _emissive;

		float _specularPower; // �d�x
		float _shininess; // ��
		float _transparencyFactor; // �����x
	};

}

#endif