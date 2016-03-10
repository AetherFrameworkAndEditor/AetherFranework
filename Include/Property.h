#ifndef _PROPERTY_H
#define _PROPERTY_H


#include"Transform.h"
#include"Color.h"
#include"Material.h"
namespace aetherClass{
	class Property
	{
	public:
		Property() = default;
		~Property() = default;
		Transform _transform;
		Color _color;
		Material _material;

	};
}

#endif