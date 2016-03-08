#include "Material.h"
#include <Windows.h>

using namespace aetherClass;

Material::Material(){

	SecureZeroMemory(&_ambient, sizeof(_ambient));
	SecureZeroMemory(&_diffuse, sizeof(_ambient));
	SecureZeroMemory(&_emissive, sizeof(_ambient));
	SecureZeroMemory(&_specular, sizeof(_ambient));

	SecureZeroMemory(&_specularPower, sizeof(_specularPower));
	SecureZeroMemory(&_shininess, sizeof(_shininess));
	SecureZeroMemory(&_transparencyFactor, sizeof(_transparencyFactor));

	_ambient._color._alpha = 1.0f;
	_diffuse._color._alpha = 1.0f;
	_emissive._color._alpha = 1.0f;
	_specular._color._alpha = 1.0f;
}

Material::~Material()
{
}

