/******************************************************************************/
/*! @addtogroup aetherMath
@file       LoadScreen.h
@brief     ���[�h��ʍ쐬�p���N���X

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
#ifndef _LOADSCREEN_H
#define _LOADSCREEN_H

#define WAIT_END = true;
#define WAITING = false;
namespace aetherClass{
	const bool kWaitEnd = true;
	const bool kWaitting = false;
	class LoadScreen
	{

	public:
		LoadScreen(){};
		virtual~LoadScreen() = default;
		virtual void Initialize() = 0;
		virtual void Run() = 0;
		virtual bool WaitRun(){ return kWaitEnd; }
		virtual void Finalize() = 0;

	};
}
#endif