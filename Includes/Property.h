/******************************************************************************/
/*! @addtogroup aetherClass
@file      Property.h
@brief     ��{�����܂Ƃ߂��N���X

*******************************************************************************
@date       2016/2/15
@author     ���q�a��
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