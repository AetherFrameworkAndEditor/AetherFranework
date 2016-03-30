/******************************************************************************/
/*! @addtogroup aetherClass
@file      Coroutine.h
@brief     疑似コルーチン用クラス。このクラスを基底クラスと置くことで使用可能

*******************************************************************************
@date       2015/12/23
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _Coroutine_H
#define _Coroutine_H
#include <stdio.h>
namespace aetherClass{
	class Coroutine{
	protected:
		int m_state;
	public:
		Coroutine() :m_state(NULL){}
		virtual ~Coroutine() = default;
	

	};
}
#define CoroutineBegin() switch(m_state){case NULL:
#define CoroutineEnd()   m_state = NULL; default: break;}
#define yieldReturnFalse {m_state = __LINE__; return false; case __LINE__:;}
#define yieldReturn {m_state = __LINE__; return; case __LINE__:;}

#endif