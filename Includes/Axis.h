#ifndef _AXIS_H
#define _AXIS_H
/******************************************************************************/
/*! @addtogroup aetherClass
@file      Axis.h
@brief     分離軸クラス

*******************************************************************************
@date       2015/12/23
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu
******************************************************************************/
#include "Vector3.h"

namespace aetherClass{
	class Axis
	{
	public:
		Axis();
		Axis(Vector3,Vector3,Vector3);
		~Axis();

		/*
		@brief          引数の回転情報から分離軸を更新
		@param[in]      回転情報
		@return         none
		@exception      none
		*/
		void Update(Vector3 rotation);

	public:
		Vector3 _axisX;
		Vector3 _axisY;
		Vector3 _axisZ;
	};
}
#endif
