#ifndef _AXIS_H
#define _AXIS_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Axis.h
@brief     ���N���X

*******************************************************************************
@date       2015/12/23
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/23 ���{�q
-# Initial Version
******************************************************************************/
#include "Vector3.h"

namespace aetherClass{
	class Axis
	{
	public:
		Axis();
		Axis(Vector3,Vector3,Vector3);
		~Axis();

		void Update(Vector3 rotation);

	public:
		Vector3 _axisX;
		Vector3 _axisY;
		Vector3 _axisZ;
	};
}
#endif