/******************************************************************************/
/*! @addtogroup aetherMath
@file      NullLoadScreen.h
@brief     Nullオブジェクト

*******************************************************************************
@date       2015/12/23
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

*******************************************************************************
@par        History
- 2015/12/23 橋本航
-# Initial Version
******************************************************************************/
#ifndef _NULLLOADSCREEN_H
#define _NULLLOADSCREEN_H
#include "LoadScreen.h"
namespace aetherClass{
	class NullLoadScreen :
		public LoadScreen
	{
	public:
		NullLoadScreen(){}
		~NullLoadScreen(){}

		void Run()override{}
		void Initialize()override{}
		void Finalize() override{}
	};
}
#endif