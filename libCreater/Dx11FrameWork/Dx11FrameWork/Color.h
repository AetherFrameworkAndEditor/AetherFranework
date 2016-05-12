#ifndef _COLOR_H
#define _COLOR_H
/******************************************************************************/
/*! @addtogroup aetherClass
    @file       Color.h
    @brief     RGBA(色)を管理するクラス

*******************************************************************************
    @date       2015/12/23
    @author     橋本航
    @par        1.0
    $Id$
    @par        Team Hurusu
  
******************************************************************************/
#include"Vector3.h"
#include"Vector4.h"
namespace aetherClass{

	class Color
	{
	public:
		Color();
		Color(float);
		Color(float,float,float,float);
		Color(Vector4);
		Color(Vector3);
		~Color();

	public:
		float _red;
		float _green;
		float _blue;
		float _alpha;
	
	public:
		Color operator -();
		void operator = (Vector3);
		void operator = (Vector4);
		void operator = (float);

		Color operator + (Color);
		Color operator + (Vector3);
		Color operator + (Vector4);
		Color operator + (float);

		void operator += (Color);
		void operator += (Vector3);
		void operator += (Vector4);
		void operator += (float);

		Color operator - (Color);
		Color operator - (Vector3);
		Color operator - (Vector4);
		Color operator - (float);

		void operator -= (Color);
		void operator -= (Vector3);
		void operator -= (Vector4);
		void operator -= (float);
	};


}
#endif