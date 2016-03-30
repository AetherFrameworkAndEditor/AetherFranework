/******************************************************************************/
/*! @addtogroup aetherClass
@file      World.h
@brief     独自形式ファイルから読み込んだ情報を格納する構造体

*******************************************************************************
@date       2016/3/7
@author     橋木航
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/

#ifndef _WORLD_H
#define _WORLD_H
#include <string>
#include <vector>
#include "Color.h"
#include "Transform.h"
#include "Material.h"
#include "Texture.h"

/*
@brief     カメラは位置と回転度の情報を読み取る
*/
struct CameraValue{
	aetherClass::Vector3 _position;
	aetherClass::Vector3 _rotation;
};

/*
@brief     オブジェクトとして読み取る情報はこの情報以上には読み込まない
           (プリミティブ、スプライト、FBX)
*/
struct ObjectInfo
{
	ObjectInfo(){
		Reset();
	}

	~ObjectInfo(){
		Reset();
	}
	aetherClass::Transform _transform;
	int _materialID;
	std::string _modelType;
	aetherClass::Color _color;
	int _textureID;
	std::string _name;
	std::string _path;

private:
	void Reset(){
		_materialID = 0;
		_modelType = "none";
		_color = aetherClass::Color(0, 0, 0, 1);
		_textureID = 0;
		_name = "none";
		_path = "null";
	}
};

/*
@brief     情報を格納するときの変数はこの型を使う
*/
struct World{
	std::vector<ObjectInfo*> _object;
	std::vector<aetherClass::Material*> _material;
	std::vector<aetherClass::Texture*> _texture;
	CameraValue _camera;
	aetherClass::Vector3 _lightPosition;
};
#endif