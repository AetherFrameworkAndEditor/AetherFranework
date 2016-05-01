#ifndef _AETHERDEBUG_H
#define _AETHERDEBUG_H
#include <iostream>
class Debug
{
public:
	Debug();
	~Debug();

	static void Print(std::string, std::string fileName, const int line);
};

#endif