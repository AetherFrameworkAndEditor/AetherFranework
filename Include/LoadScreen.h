/******************************************************************************/
/*! @addtogroup aetherMath
@file       LoadScreen.h
@brief     ロード画面作成用基底クラス

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