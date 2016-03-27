#ifndef _LIGHT_H
#define _LIGHT_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Light.h
@brief     ライトオブジェクト

*******************************************************************************
@date       2016/1/18
@author     金子和樹
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/
#include "Vector3.h"
#include "Triangle.h"
#include <memory>
namespace aetherClass{
	class Light
	{
		struct Property{
			Vector3 _translation;
		};
	public:
		Light() = default;
		~Light() = default;

		Property property;
	private:
		float Padding;

	};
}
#endif