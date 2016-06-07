/******************************************************************************/
/*! @addtogroup aetherClass
@file      Direct3DManager.h
@brief     Direct3Dの初期化

*******************************************************************************
@date       2015/12/23
@author     橋本航
@par        1.0
$Id$
@par        Team Hurusu

******************************************************************************/
#ifndef _DIRECT3DMANAGER_H
#define _DIRECT3DMANAGER_H

// 必要なライブラリをリンク
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3d11.lib")

// C4005の警告を非表示にする
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
		@brief         DirectXの初期化
		@param[in]      screen          画面のサイズ
		@param[in]      vsync           true:/false:  
		@param[in]      *hwnd			ウィンドウハンドルリスト
		@param[in]      numWindow		ウィンドウ数
		@param[in]      isFullScreen    true: フルスクリーンモード / false: ウィンドウモード
		@param[in]      screenDepth     画面の奥行の最大値を0.0以上の値で設定
		@param[in]      screenNear      画面の近さを0.0以上の値で設定
		@return         成功時: true / 失敗時: false
		@exception      none
		*/
		bool Initialize(Vector2 screen, bool vsync, WindowBase** hWNd,UINT numWindow, bool isFullScreen, float screenDepth, float screenNear);

		/*
		@brief          解放処理
		@param          none
		@return         none
		@exception      none
		*/
		void Finalize();

		/*
		@brief          画面全体を引数の色で塗りつぶし、すべてのウィンドウを初期化する   
		@param[in]      Color    画面を塗りつぶす色
		@return         none
		@exception      none
		*/
		void BeginScene(Color);

		/*
		@brief          フロントバッファとバックバッファの切り替え    
		@param          none
		@return         none
		@exception      none
		*/
		void EndScene();

		/*
		@brief          デバイスの取得
		@param          none
		@return         none
		@exception      none
		*/
		ID3D11Device* GetDevice();

		/*
		@brief          デバイスコンテキストの取得
		@param          none
		@return         none
		@exception      none
		*/
		ID3D11DeviceContext* GetDeviceContext();

		/*
		@brief          Projection行列の取得
		@param[in/out]  none
		@return         Matrix4x4型オブジェクト
		@exception      none
		*/
		Matrix4x4 GetProjectionMatrix();

		/*
		@brief          World行列の取得
		@param[in/out]  none
		@return         Matrix4x4型オブジェクト
		@exception      none
		*/
		Matrix4x4 GetWorldMatrix();

		/*
		@brief          Ortho行列の取得
		@param[in/out]  none
		@return         Matrix4x4型オブジェクト
		@exception      none
		*/
		Matrix4x4 GetOrthoMatrix();

		/*
		@brief          視野角パース行列の取得
		@param[in/out]  none
		@return         Matrix4x4型オブジェクト
		@exception      none
		*/
		Matrix4x4 GetPerspectiveFovMatrix();

		/*
		@brief          ビデオカードの情報を取得
		@param[in]      cardname
		@param[in/out]  memory
		@return         none
		@exception      none
		*/
		void GetVideoCardInfo(char* cardname, int& memory);

		/*
		@brief          Projection行列の代入
		@param[in/out]  matrix
		@return         none
		@exception      none
		*/
		void SetProjectionMatrix(Matrix4x4& matrix);

		/*
		@brief          ２次元描画モードへ切り替える
		@param[in/out]  none
		@return         none
		@exception      none
		*/
		void Change2DMode();

		/*
		@brief          ３次元描画モードへ切り替える
		@param[in/out]  none
		@return         none
		@exception      none
		*/
		void Change3DMode();

		/*
		@brief          遠クリップ面の取得
		@param[in/out]  none
		@return         ScreenDepth
		@exception      none
		*/
		int GetScreenDepth();

		/*
		@brief          近クリップ面の取得
		@param[in/out]  none
		@return         ScreenNear
		@exception      none
		*/
		int GetScreenNear();

		/*
		@brief          レンダリング対象のウィンドウ
		@param[in/out]  対象のウィンドウ番号
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