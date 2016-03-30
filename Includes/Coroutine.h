/******************************************************************************/
/*! @addtogroup aetherClass
@file      Coroutine.h
@brief     �^���R���[�`���p�N���X�B���̃N���X�����N���X�ƒu�����ƂŎg�p�\

*******************************************************************************
@date       2015/12/23
@author     ���{�q
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