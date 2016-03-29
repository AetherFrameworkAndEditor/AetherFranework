/******************************************************************************/
/*! @addtogroup aetherMath
@file      NullScene.h
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
#ifndef _NULLSCENE_H
#define _NULLSCENE_H
#include "GameScene.h"
namespace aetherClass{
	class NullScene :
		public aetherClass::GameScene
	{
		public:
			NullScene() :
				GameScene("null", GetManager()){
			}
			~NullScene(){}

			bool Initialize()override{ return true; }
			void Render()override{}
			bool Updater()override{ return true; }
			void Finalize()override{}

		private:
			static std::string m_name;
	};
}
#endif