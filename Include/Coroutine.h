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