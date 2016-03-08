#include "DirectXEntity.h"

using namespace aetherClass;

Direct3DManager* DirectXEntity::m_direct3d = nullptr;
std::unordered_map<std::wstring, WindowBase*> DirectXEntity::m_window;

DirectXEntity::DirectXEntity()
{
}


DirectXEntity::~DirectXEntity()
{
}



void DirectXEntity::CopyDirectX(Direct3DManager* manager,WindowBase** window,UINT numWindow){
	m_direct3d = manager;
	for (UINT i = 0; i < numWindow; ++i)
	{
		m_window[window[i]->GetWindowName()] = window[i];
	}

}

//
Direct3DManager* DirectXEntity::GetDirect3DManager()const{
	return m_direct3d;
}

//
HWND& DirectXEntity::GetWindowHandle(std::wstring numWindow)const{
	HWND hWnd = NULL;
	
	if (m_window.count(numWindow)){
		hWnd = m_window[numWindow]->GetWindowHandle();
	}
	return hWnd;
}
HWND& DirectXEntity::GetWindowHandle()const{
		HWND hWnd = NULL;
		hWnd = m_window.begin()->second->GetWindowHandle();
		return hWnd;
}