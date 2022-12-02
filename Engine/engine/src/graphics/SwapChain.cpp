#include "SwapChain.h"
#include "engine/src/utility/exception/ExeptionMacros.h"

namespace engine::graphics {
	IDXGISwapChain* SwapChain::GetSwapChain() noexcept
	{
		return m_SwapChain.Get();
	}

	void SwapChain::Init(HWND windowID)
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
		swapChainDesc.BufferDesc.Width = 0;
		swapChainDesc.BufferDesc.Height = 0;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = windowID;
		swapChainDesc.Windowed = true;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = 0;

		auto& device = D3DDevice::Get();
		HRESULT hr = device.m_DXGIFactory->CreateSwapChain(device.m_D3DDevice.Get(), &swapChainDesc, &m_SwapChain);
		THROW_EXCEPTION_IF_HRESULT_ERROR(hr, "SWAP CHAIN", "Swap chain creation failed");



		Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer = nullptr;
		THROW_EXCEPTION_IF_HRESULT_ERROR(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer),
			"SWAP CHAIN", "Getting back buffer from current swap chain failed!");


		THROW_EXCEPTION_IF_HRESULT_ERROR(D3DDevice::Get().GetDevice()->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_RenderTargetView),
			"SWAP CHAIN", "Render Target View creation failed!");


		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = true;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState = nullptr;
		THROW_EXCEPTION_IF_HRESULT_ERROR(D3DDevice::Get().GetDevice()->CreateDepthStencilState(&dsDesc, &m_DepthStencilState),
			"SWAP CHAIN", "Depth Stencil State creation failed!");
		D3DDevice::Get().GetImmediateDeviceContext()->OMSetDepthStencilState(m_DepthStencilState.Get(), 1u);


		RECT clientRect = { 0 };
		GetClientRect(GetForegroundWindow(), &clientRect);

		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencil = nullptr;
		D3D11_TEXTURE2D_DESC depthDesc = { 0 };
		depthDesc.Width = clientRect.right - clientRect.left;
		depthDesc.Height = clientRect.bottom - clientRect.top;
		depthDesc.MipLevels = 1u;
		depthDesc.ArraySize = 1u;
		depthDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthDesc.SampleDesc.Count = 1u;
		depthDesc.SampleDesc.Quality = 0u;
		depthDesc.Usage = D3D11_USAGE_DEFAULT;
		depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		THROW_EXCEPTION_IF_HRESULT_ERROR(D3DDevice::Get().GetDevice()->CreateTexture2D(&depthDesc, nullptr, &depthStencil),
			"SWAP CHAIN", "Depth stencil buffer creation failed!");


		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		memset(&depthStencilViewDesc, 0, sizeof(depthStencilViewDesc));
		depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0u;
		THROW_EXCEPTION_IF_HRESULT_ERROR(D3DDevice::Get().GetDevice()->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, &m_DepthStencilView),
			"SWAP CHAIN", "Depth stencil view creation failed!");

		D3DDevice::Get().GetImmediateDeviceContext()->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());

		D3D11_VIEWPORT viewPort = { 0 };
		viewPort.Width = clientRect.right - clientRect.left;
		viewPort.Height = clientRect.bottom - clientRect.top;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		D3DDevice::Get().GetImmediateDeviceContext()->RSSetViewports(1, &viewPort);
	}

	void SwapChain::ClearBuffers(float r, float g, float b, float a) const noexcept
	{
		auto immContext = D3DDevice::Get().GetImmediateDeviceContext();

		float color[] = { r, g, b, a };
		immContext->ClearRenderTargetView(m_RenderTargetView.Get(), color);
		immContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
	}
}