/******************************************************************************/
/*! @addtogroup aetherClass
@file      ConsoleWindow.h
@brief     コンソールウィンドウを表示する

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

#ifndef _CONSOLEWINDOW_H
#define _CONSOLEWINDOW_H
namespace aetherClass{
	class ConsoleWindow
	{
	public:
		ConsoleWindow();
		ConsoleWindow(ConsoleWindow&);
		~ConsoleWindow();
		static void Create();
		static void Close();
	private:
		
		static int m_hConsole;
	};
}
#endif