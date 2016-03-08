#include "DirectXEntity.h"

using namespace aetherClass;

Direct3DManager* DirectXEntity::m_direct3d = nullptr;
HWND DirectXEntity::m_hWnd = NULL;
DirectXEntity::DirectXEntity()
{
}


DirectXEntity::~DirectXEntity()
{
}



void DirectXEntity::CopyDirectX(Direct3DManager* manager,const HWND hWnd){
	m_direct3d = manager;
	m_hWnd = hWnd;
}

//
Direct3DManager* DirectXEntity::GetDirect3DManager()const{
	return m_direct3d;
}

//
HWND& DirectXEntity::GetWindowHandle()const{
	return m_hWnd;
}