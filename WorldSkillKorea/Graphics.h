#pragma once
#include <D3D11.h>

const class Graphics
{
public:
	Graphics() = delete;
	Graphics(Graphics&) = delete;
	Graphics(HWND windowHandle);
	~Graphics();

	void draw();
	ID3D11Device* getDevice() const;
private:
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_DeviceContext;
	IDXGISwapChain* m_SwapChain;
	ID3D11RenderTargetView* m_RenderTargetView;
	D3D_FEATURE_LEVEL m_FeatureLevel;
	UINT m_4xMsaaQuality;
	ID3D11Texture2D* m_DepthStencilBuffer;
	ID3D11DepthStencilView* m_DepthStencilView;
};