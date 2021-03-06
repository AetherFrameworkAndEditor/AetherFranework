#include "Direct3DManager.h"
#include "DirectXEntity.h"
using namespace aetherClass;
using namespace DirectX;
Direct3DManager::Direct3DManager(){

	m_device = nullptr;
	m_deviceContext = nullptr;

	m_depthStencilState = nullptr;
	m_rasterState = nullptr;

}

Direct3DManager::~Direct3DManager(){}

bool Direct3DManager::Initialize(Vector2 screen, bool vsync, WindowBase **window,
	UINT numWindow,bool isFullScreen, float screenDepth, float screenNear){
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes, numerator, denominator, stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	int error;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Texture2D* backBufferPtr;
	ID3D11BlendState* blendState = NULL;

	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_VIEWPORT viewport;
	D3D11_BLEND_DESC blendStateDesc;

	float fieldOfView, screenAspect;

	// Store the vsync setting.
	m_vsyncEnabled = vsync;

	// Create a DirectX graphics interface factory.
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result))
	{
		return false;
	}

	// Use the factory to create an adapter for the primary graphics interface (video card).
	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))
	{
		return false;
	}

	// Enumerate the primary adapter output (monitor).
	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))
	{
		return false;
	}

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Create a list to hold all the possible display modes for this monitor/video card combination.
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
	{
		return false;
	}

	// Now fill the display mode list structures.
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(result))
	{
		return false;
	}

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	for (int i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)screen._x)
		{
			if (displayModeList[i].Height == (unsigned int)screen._y)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}


	// Get the adapter (video card) description.
	result = adapter->GetDesc(&adapterDesc);
	if (FAILED(result))
	{
		return false;
	}

	// Store the dedicated video card memory in megabytes.
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Convert the name of the video card to a character array and store it.
	error = wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128);
	if (error != 0)
	{
		return false;
	}



	// Initialize the swap chain description.
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set to a single back buffer.
	swapChainDesc.BufferCount = 1;

	// Set the width and height of the back buffer.
	swapChainDesc.BufferDesc.Width = screen._x;
	swapChainDesc.BufferDesc.Height = screen._y;

	// Set regular 32-bit surface for the back buffer.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set the refresh rate of the back buffer.
	if (m_vsyncEnabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	// Set the usage of the back buffer.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.

	// Turn multisampling off.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	// Set to full screen or windowed mode.
	if (isFullScreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	// Set the scan line ordering and scaling to unspecified.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	swapChainDesc.Flags = 0;

	// Set the feature level to DirectX 11.
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	result = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION,
		&m_device, NULL, &m_deviceContext);
	if (FAILED(result)){
		return false;
	}

	//// Create the swap chain, Direct3D device, and Direct3D device context.
	//result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1,
	//	D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_deviceContext);

	//if (FAILED(result))
	//{
	//	return false;
	//}


	for (UINT i = 0; i < numWindow; ++i) {
		swapChainDesc.OutputWindow = window[i]->GetWindowHandle();
		std::wstring name = window[i]->GetWindowName();

		factory->CreateSwapChain(m_device, &swapChainDesc, &m_swapChain[name]);
		result = m_swapChain[name]->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
		if (FAILED(result)){
			return false;
		}

		// Create the render target view with the back buffer pointer.
		result = m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView[name]);
		if (FAILED(result)){
			return false;
		}

		// Release pointer to the back buffer as we no longer need it.
		backBufferPtr->Release();
		backBufferPtr = nullptr;
	}




	// Initialize the description of the depth buffer.
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = screen._x;
	depthBufferDesc.Height = screen._y;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;
	
	for (int i = 0; i < numWindow; ++i){
		std::wstring name = window[i]->GetWindowName();

		// Create the texture for the depth buffer using the filled out description.
		result = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer[name]);
		if (FAILED(result))
		{
			return false;
		}

	}

	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
	if (FAILED(result))
	{
		return false;
	}
	// Set the depth stencil state.
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

	//Create ther depth stencil state. depthEnable false mode for 2D.
	depthStencilDesc.DepthEnable = false;
	result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilDisableState);
	if (FAILED(result)){
		return false;
	}

	// Initailze the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	for (int i = 0; i < numWindow; ++i){
		std::wstring name = window[i]->GetWindowName();

		result = m_device->CreateDepthStencilView(m_depthStencilBuffer[name], &depthStencilViewDesc, &m_depthStencilView[name]);
		if (FAILED(result))
		{
			return false;
		}

	}
	std::wstring firstname = window[0]->GetWindowName();
	// Bind the render target view and depth stencil buffer to the output render pipeline.
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView[firstname], m_depthStencilView[firstname]);

	// Setup the raster description which will determine how and what polygons will be drawn.
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_NONE;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	if (FAILED(result))
	{
		return false;
	}

	// Now set the rasterizer state.
	m_deviceContext->RSSetState(m_rasterState);

	blendStateDesc.AlphaToCoverageEnable = FALSE;
	blendStateDesc.IndependentBlendEnable = FALSE;
	for (int i = 0; i < 8; i++){
		blendStateDesc.RenderTarget[i].BlendEnable = TRUE;
		blendStateDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendStateDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendStateDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
		blendStateDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendStateDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendStateDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendStateDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}
	this->GetDevice()->CreateBlendState(&blendStateDesc, &blendState);

	//そのブレンディングをコンテキストに設定
	float blendFactor[4] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
	this->GetDeviceContext()->OMSetBlendState(blendState, blendFactor, 0xffffffff);


	// Setup the viewport for rendering.
	viewport.Width = (float)screen._x;
	viewport.Height = (float)screen._y;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	// Create the viewport.
	m_deviceContext->RSSetViewports(1, &viewport);
	
	// Setup the projection matrix.
	fieldOfView = (float)kAetherPI / 4.0f;
	screenAspect = (float)screen._x / (float)screen._y;

	// Initialize the world matrix to the identity matrix.
	m_worldMatrix.Identity();

	// Create the projection matrix for 3D rendering.
	m_perspectiveFovMatrix.PerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);

	// Create an orthographic projection matrix for 2D rendering.
	m_orthoMatrix.OrthoLH((float)screen._x, (float)screen._y, screenNear, screenDepth);

	//Set projection matrix,default State is 3D rendering mode.
	this->SetProjectionMatrix(m_perspectiveFovMatrix);

	D3D11_BLEND_DESC blendStateDescription;
	// Clear the blend state description.
	ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));

	// Create an alpha enabled blend state description.
	blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	// Create the blend state using the description.
	result = m_device->CreateBlendState(&blendStateDescription, &m_alphaEnableBlendingState);
	if (FAILED(result))
	{
		return false;
	}

	// Modify the description to create an alpha disabled blend state description.
	blendStateDescription.RenderTarget[0].BlendEnable = FALSE;

	// Create the blend state using the description.
	result = m_device->CreateBlendState(&blendStateDescription, &m_alphaDisableBlendingState);
	if (FAILED(result))
	{
		return false;
	}

	// Direct3DManagerとWindowHandleの取得
	DirectXEntity::CopyDirectX(this, window,numWindow);
	m_screenDepth = screenDepth;
	m_screenNear = screenNear;
	m_numWindows = numWindow;

	// Release the display mode list.
	delete[] displayModeList;
	displayModeList = nullptr;

	// Release the adapter output.
	adapterOutput->Release();
	adapterOutput = nullptr;

	// Release the adapter.
	adapter->Release();
	adapter = nullptr;

	// Release the factory.
	factory->Release();
	factory = nullptr;

	return true;
}


void Direct3DManager::Finalize(){

	// Before shutting down set to windowed mode or when you release the swap chain it will throw an exception

	if (m_alphaEnableBlendingState)
	{
		m_alphaEnableBlendingState->Release();
		m_alphaEnableBlendingState = 0;
	}

	if (m_alphaDisableBlendingState)
	{
		m_alphaDisableBlendingState->Release();
		m_alphaDisableBlendingState = 0;
	}


	if (m_rasterState)
	{
		m_rasterState->Release();
		m_rasterState = nullptr;
	}


	if (m_depthStencilState)
	{
		m_depthStencilState->Release();
		m_depthStencilState = nullptr;
	}
	if (m_depthStencilDisableState)
	{
		m_depthStencilDisableState->Release();
		m_depthStencilDisableState = nullptr;
	}

	for each (auto i in m_depthStencilBuffer)
	{

		if (m_depthStencilBuffer[i.first])
		{
			m_depthStencilBuffer[i.first]->Release();
			m_depthStencilBuffer[i.first] = nullptr;
		}
		if (m_renderTargetView[i.first])
		{
			m_renderTargetView[i.first]->Release();
			m_renderTargetView[i.first] = nullptr;
		}
		if (m_depthStencilView[i.first])
		{
			m_depthStencilView[i.first]->Release();
			m_depthStencilView[i.first] = nullptr;
		}
	}

	if (m_deviceContext)
	{
		m_deviceContext->Release();
		m_deviceContext = nullptr;
	}

	if (m_device)
	{
		m_device->Release();
		m_device = nullptr;
	}
	for each (auto i in m_swapChain)
	{
		if (i.second)
		{
			i.second->Release();
			i.second = nullptr;
		}
	}

	return;
}

void Direct3DManager::BeginScene(Color selectColor){
	// Setup the color to clear the buffer to
	const float color[4] = {
		selectColor._red,
		selectColor._green,
		selectColor._blue,
		selectColor._alpha
	};
	
	for each (auto i in m_renderTargetView)
	{
		// Clear the back buffer.
		m_deviceContext->ClearRenderTargetView(m_renderTargetView[i.first], color);
		m_deviceContext->ClearDepthStencilView(m_depthStencilView[i.first], D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
	return;
}

void Direct3DManager::EndScene(){
	// Present the back buffer to the screen since rendering is complete
	if (m_vsyncEnabled)
	{
		for each (auto i in m_swapChain)
		{
			// Lock to screen refresh rate
			i.second->Present(1, 0);
		}
	}
	else
	{
		for each (auto i in m_swapChain)
		{
			// Lock to screen refresh rate
			i.second->Present(0, 0);
		}
	}
	return;
}

void Direct3DManager::SetTargetWindow(std::wstring numWindow){
	if(!m_renderTargetView.count(numWindow))return;
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView[numWindow], m_depthStencilView[numWindow]);
}

// helper function
ID3D11Device* Direct3DManager::GetDevice(){
	return m_device;
}

ID3D11DeviceContext* Direct3DManager::GetDeviceContext(){
	return m_deviceContext;
}


Matrix4x4 Direct3DManager::GetProjectionMatrix(){
	return m_projectionMatrix;
}

Matrix4x4 Direct3DManager::GetWorldMatrix(){
	return m_worldMatrix;
}

Matrix4x4 Direct3DManager::GetOrthoMatrix(){
	return m_orthoMatrix;
}

Matrix4x4 Direct3DManager::GetPerspectiveFovMatrix(){
	return m_perspectiveFovMatrix;
}

void Direct3DManager::SetProjectionMatrix(Matrix4x4& matrix){
	m_projectionMatrix = matrix;
}

void Direct3DManager::Change2DMode(){
	m_deviceContext->OMSetDepthStencilState(m_depthStencilDisableState, 1);
	SetProjectionMatrix(m_orthoMatrix);
}
void Direct3DManager::Change3DMode(){
	m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);
	SetProjectionMatrix(m_perspectiveFovMatrix);
}

void Direct3DManager::GetVideoCardInfo(char* cardName, int& memory){
	strcpy_s(cardName, 128, m_videoCardDescription);
	memory = m_videoCardMemory;

	return;
}


void Direct3DManager::EnableAlphaBlending()
{
	float blendFactor[4];


	// Setup the blend factor.
	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	// Turn on the alpha blending.
	m_deviceContext->OMSetBlendState(m_alphaEnableBlendingState, blendFactor, 0xffffffff);

	return;
}


void Direct3DManager::DisableAlphaBlending()
{
	float blendFactor[4];


	// Setup the blend factor.
	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	// Turn off the alpha blending.
	m_deviceContext->OMSetBlendState(m_alphaDisableBlendingState, blendFactor, 0xffffffff);

	return;
}

int Direct3DManager::GetScreenDepth() {
	return m_screenDepth;
}

int Direct3DManager::GetScreenNear() {
	return m_screenNear;
}