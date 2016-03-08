/******************************************************************************/
/*! @addtogroup aetherMath
@file      NullLoadScreen.h
@brief     Null�I�u�W�F�N�g

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