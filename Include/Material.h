/******************************************************************************/
/*! @addtogroup aetherClass
@file      Material.h
@brief     マテリアルのパラメーターを保持する変数があるクラス

*******************************************************************************
@date       2015/12/27
@author    金子 和樹
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/27 金子 和樹
-# Initial Version
- 2015/12/27 橋本 航
-# 新しい設計に合わせた
- 2015/12/27 橋本 航
-# delete GetMaterial function
- 2015/12/27 橋本 航
-# add MaterialElement struct
******************************************************************************/
#ifndef _MATERIAL_H
#define _MATERIAL_H
#include <vector>
#include"Vector4.h"
#include"Vector3.h"
#include"Texture.h"
namespace aetherClass{
	
	// マテリアルの要素構造体
	struct MaterialElement{
		enum class eMaterialElementType{
			eElementNone = 0,
			eElementColor,
			eElementTexture,
			eElementBoth,
			eElementMax
		};

		// UVSet名とテクスチャのパス名.1つのUVSet名に対してテクスチャが複数ある場合がある
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

		// FBXのマテリアルは二種類しかない
		enum class eFbxMaterialType{
			eMaterialLambert = 0,
			eMaterialPhong
		};

		eFbxMaterialType _type;

		MaterialElement _ambient;
		MaterialElement _specular;
		MaterialElement _diffuse;
		MaterialElement _emissive;

		float _specularPower; // 硬度
		float _shininess; // 光
		float _transparencyFactor; // 透明度
	};

}

#endif