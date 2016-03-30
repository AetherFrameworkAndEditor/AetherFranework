/******************************************************************************/
/*! @addtogroup aetherClass
@file      ConsoleWindow.h
@brief     �R���\�[���E�B���h�E��\������

*******************************************************************************
@date       2015/12/23
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

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