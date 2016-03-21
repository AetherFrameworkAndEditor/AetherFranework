#ifndef _WORLD_H
#define _WORLD_H
#include <string>
#include <vector>
#include "Color.h"
#include "Transform.h"
#include "Material.h"
#include "Texture.h"
struct CameraValue{
	aetherClass::Vector3 _position;
	aetherClass::Vector3 _rotation;
};

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
struct World{
	std::vector<ObjectInfo*> _object;
	std::vector<aetherClass::Material*> _material;
	std::vector<aetherClass::Texture*> _texture;
	CameraValue _camera;
	aetherClass::Vector3 _lightPosition;
};
#endif