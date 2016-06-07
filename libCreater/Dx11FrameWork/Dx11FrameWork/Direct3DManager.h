/******************************************************************************/
/*! @addtogroup aetherClass
@file      Direct3DManager.h
@brief     Direct3D�̏�����

*******************************************************************************
@date       2015/12/23
@author     ���{�q
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _DIRECT3DMANAGER_H
#define _DIRECT3DMANAGER_H

// �K�v�ȃ��C�u�����������N
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3d11.lib")

// C4005�̌x�����\���ɂ���
#pragma warning(disable : 4005) 

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "Color.h"
#include "MathUtility.h"
#include"Matrix4x4.h"
#include<vector>
#include"WindowBase.h"
#include<unordered_map>
namespace aetherClass{
	
	class Direct3DManager{

	public:
		Direct3DManager();
		~Direct3DManager();
		/*
		@brief         DirectX�̏�����
		@param[in]      screen          ��ʂ̃T�C�Y
		@param[in]      vsync           true:/false:  
		@param[in]      *hwnd			�E�B���h�E�n���h�����X�g
		@param[in]      numWindow		�E�B���h�E��
		@param[in]      isFullScreen    true: �t���X�N���[�����[�h / false: �E�B���h�E���[�h
		@param[in]      screenDepth     ��ʂ̉��s�̍ő�l��0.0�ȏ�̒l�Őݒ�
		@param[in]      screenNear      ��ʂ̋߂���0.0�ȏ�̒l�Őݒ�
		@return         ������: true / ���s��: false
		@exception      none
		*/
		bool Initialize(Vector2 screen, bool vsync, WindowBase** hWNd,UINT numWindow, bool isFullScreen, float screenDepth, float screenNear);

		/*
		@brief          �������
		@param          none
		@return         none
		@exception      none
		*/
		void Finalize();

		/*
		@brief          ��ʑS�̂������̐F�œh��Ԃ��A���ׂẴE�B���h�E������������   
		@param[in]      Color    ��ʂ�h��Ԃ��F
		@return         none
		@exception      none
		*/
		void BeginScene(Color);

		/*
		@brief          �t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̐؂�ւ�    
		@param          none
		@return         none
		@exception      none
		*/
		void EndScene();

		/*
		@brief          �f�o�C�X�̎擾
		@param          none
		@return         none
		@exception      none
		*/
		ID3D11Device* GetDevice();

		/*
		@brief          �f�o�C�X�R���e�L�X�g�̎擾
		@param          none
		@return         none
		@exception      none
		*/
		ID3D11DeviceContext* GetDeviceContext();

		/*
		@brief          Projection�s��̎擾
		@param[in/out]  none
		@return         Matrix4x4�^�I�u�W�F�N�g
		@exception      none
		*/
		Matrix4x4 GetProjectionMatrix();

		/*
		@brief          World�s��̎擾
		@param[in/out]  none
		@return         Matrix4x4�^�I�u�W�F�N�g
		@exception      none
		*/
		Matrix4x4 GetWorldMatrix();

		/*
		@brief          Ortho�s��̎擾
		@param[in/out]  none
		@return         Matrix4x4�^�I�u�W�F�N�g
		@exception      none
		*/
		Matrix4x4 GetOrthoMatrix();

		/*
		@brief          ����p�p�[�X�s��̎擾
		@param[in/out]  none
		@return         Matrix4x4�^�I�u�W�F�N�g
		@exception      none
		*/
		Matrix4x4 GetPerspectiveFovMatrix();

		/*
		@brief          �r�f�I�J�[�h�̏����擾
		@param[in]      cardname
		@param[in/out]  memory
		@return         none
		@exception      none
		*/
		void GetVideoCardInfo(char* cardname, int& memory);

		/*
		@brief          Projection�s��̑��
		@param[in/out]  matrix
		@return         none
		@exception      none
		*/
		void SetProjectionMatrix(Matrix4x4& matrix);

		/*
		@brief          �Q�����`�惂�[�h�֐؂�ւ���
		@param[in/out]  none
		@return         none
		@exception      none
		*/
		void Change2DMode();

		/*
		@brief          �R�����`�惂�[�h�֐؂�ւ���
		@param[in/out]  none
		@return         none
		@exception      none
		*/
		void Change3DMode();

		/*
		@brief          ���N���b�v�ʂ̎擾
		@param[in/out]  none
		@return         ScreenDepth
		@exception      none
		*/
		int GetScreenDepth();

		/*
		@brief          �߃N���b�v�ʂ̎擾
		@param[in/out]  none
		@return         ScreenNear
		@exception      none
		*/
		int GetScreenNear();

		/*
		@brief          �����_�����O�Ώۂ̃E�B���h�E
		@param[in/out]  �Ώۂ̃E�B���h�E�ԍ�
		@return         none
		@exception      none
		*/
		void SetTargetWindow(std::wstring);

		void EnableAlphaBlending();
		void DisableAlphaBlending();

	private:
		bool m_vsyncEnabled;
		int m_videoCardMemory;
		char m_videoCardDescription[128];
		int m_screenNear, m_screenDepth;
		UINT m_numWindows;

		ID3D11Device *m_device;
		ID3D11DeviceContext *m_deviceContext;

		std::unordered_map<std::wstring,IDXGISwapChain*>m_swapChain;
		std::unordered_map<std::wstring, ID3D11RenderTargetView *>m_renderTargetView;
		std::unordered_map<std::wstring, ID3D11DepthStencilView *>m_depthStencilView;
		std::unordered_map<std::wstring, ID3D11Texture2D *>m_depthStencilBuffer;

		ID3D11DepthStencilState *m_depthStencilState, *m_depthStencilDisableState;

		ID3D11RasterizerState *m_rasterState;
		ID3D11BlendState* m_alphaEnableBlendingState;
		ID3D11BlendState* m_alphaDisableBlendingState;
		Matrix4x4 m_projectionMatrix;
		Matrix4x4 m_worldMatrix;
		Matrix4x4 m_orthoMatrix;
		Matrix4x4 m_perspectiveFovMatrix;

	};
}
#endif