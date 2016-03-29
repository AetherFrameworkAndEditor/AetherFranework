/******************************************************************************/
/*! @addtogroup aetherClass
@file      Property.h
@brief     基本情報をまとめたクラス

*******************************************************************************
@date       2016/2/15
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/

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