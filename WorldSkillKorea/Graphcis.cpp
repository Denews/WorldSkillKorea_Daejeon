#include "Graphics.h"
#include "GameConstants.h"

Graphics::Graphics(HWND windowHandle) :
	m_Device(nullptr),
	m_DeviceContext(nullptr),
	m_SwapChain(nullptr),
	m_RenderTargetView(nullptr)
{
	HRESULT hr;

	UINT createDeviceFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	hr = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, createDeviceFlags, 0, 0, D3D11_SDK_VERSION,
		&m_Device, &m_FeatureLevel, &m_DeviceContext);

	if (FAILED(hr))
	{
		throw "Create Device Failed";
	}

	if (m_FeatureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		throw "DirectX 11 Unsupported";
	}

	hr = m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality);
	if (FAILED(hr))
	{
		throw "CheckMultiSampleQualityLevels Failed";
	}
	if (m_4xMsaaQuality == 0)
	{
		throw "4xMsaa Unsupported";
	}

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = GameConstants::width;
	sd.BufferDesc.Height = GameConstants::height;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferCount = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Flags = 0;
	sd.OutputWindow = windowHandle;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed = true;
	sd.SampleDesc.Count = 4;
	sd.SampleDesc.Quality = m_4xMsaaQuality - 1;

	IDXGIDevice* dxgiDevice = nullptr;
	hr = m_Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void **>(&dxgiDevice));
	if (FAILED(hr))
	{
		throw "Get DXGIDevice Failed";
	}

	IDXGIAdapter* dxgiAdapter = nullptr;
	hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void **>(&dxgiAdapter));
	if (FAILED(hr))
	{
		throw "Get DXGIAdapter Failed";
	}

	IDXGIFactory* dxgiFactory = nullptr;
	hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void **>(&dxgiFactory));
	if (FAILED(hr))
	{
		throw "Get DXGIFactory";
	}

	hr = dxgiFactory->CreateSwapChain(m_Device, &sd, &m_SwapChain);
	if (FAILED(hr))
	{
		throw "Create SwapChain Failed";
	}

	if (dxgiFactory)
	{
		dxgiFactory->Release();
		dxgiFactory = nullptr;
	}
	if (dxgiAdapter)
	{
		dxgiAdapter->Release();
		dxgiAdapter = nullptr;
	}
	if (dxgiDevice)
	{
		dxgiDevice->Release();
		dxgiDevice = nullptr;
	}
	
	ID3D11Texture2D* backBuffer = nullptr;
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&backBuffer);
	if (FAILED(hr))
	{
		throw "Get BackBuffer Failed";
	}

	hr = m_Device->CreateRenderTargetView(backBuffer, 0, &m_RenderTargetView);
	if (FAILED(hr))
	{
		throw "Create RenderTargetView Failed";
	}

	D3D11_TEXTURE2D_DESC td;
	td.ArraySize = 1;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags = 0;
	td.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	td.Height = GameConstants::height;
	td.MipLevels = 1;
	td.MiscFlags = 0;
	td.SampleDesc.Count = 4;
	td.SampleDesc.Quality = m_4xMsaaQuality - 1;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.Width = GameConstants::width;

	hr = m_Device->CreateTexture2D(&td, nullptr, &m_DepthStencilBuffer);
	if (FAILED(hr))
	{
		throw "Create DepthStencilBuffer Failed";
	}

	hr = m_Device->CreateDepthStencilView(m_DepthStencilBuffer, nullptr, &m_DepthStencilView);
	if (FAILED(hr))
	{
		throw "Create DepthStencilView Failed";
	}

	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	D3D11_VIEWPORT viewport;
	viewport.Height = GameConstants::height;
	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = GameConstants::width;

	m_DeviceContext->RSSetViewports(1, &viewport);
}

Graphics::~Graphics()
{
	if (m_DepthStencilView)
	{
		m_DepthStencilView->Release();
		m_DepthStencilView = nullptr;
	}
	if (m_DepthStencilBuffer)
	{
		m_DepthStencilBuffer->Release();
		m_DepthStencilBuffer = nullptr;
	}
	if (m_RenderTargetView)
	{
		m_RenderTargetView->Release();
		m_RenderTargetView = nullptr;
	}
	if (m_SwapChain)
	{
		m_SwapChain->Release();
		m_SwapChain = nullptr;
	}
	if (m_DeviceContext)
	{
		m_DeviceContext->Release();
		m_DeviceContext = nullptr;
	}
	if (m_Device)
	{
		m_Device->Release();
		m_Device = nullptr;
	}
}

void Graphics::draw()
{
	const float bg[4] = { 0.0f, 1.0f, 1.0f, 0.0f };
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, bg);

	m_SwapChain->Present(0, 0);
}

ID3D11Device* Graphics::getDevice() const
{
	return m_Device;
}