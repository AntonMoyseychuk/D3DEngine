#include "SwapChain.h"

namespace engine::graphics {
	SwapChain::SwapChain(HWND windowHandle, uint32_t width, uint32_t height)
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = windowHandle;
		swapChainDesc.Windowed = true;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = 0;

		auto d3dDevice = Graphics::Get().m_DeviceD3D;
		if (FAILED(Graphics::Get().m_FactoryDXGI->CreateSwapChain(d3dDevice.Get(), &swapChainDesc, &m_SwapChain))) {
			//throw exception
		}

		Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer = nullptr;
		if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer))) {
			//throw exception
		}

		if (FAILED(d3dDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_RenderTargetView))) {
			//throw exception
		}
		//THROW_D3D_EXCEPTION_MSG_IF_FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer),
		//	"m_SwapChain->GetBuffer failed!", m_DXGIInfoManager.GetMessages());
		//
		//THROW_D3D_EXCEPTION_MSG_IF_FAILED(m_Device->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_RenderTargetView),
		//	"Render Target View creation failed!", m_DXGIInfoManager.GetMessages());
		
		
		//D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		//dsDesc.DepthEnable = true;
		//dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		//dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		//Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState = nullptr;
		//THROW_D3D_EXCEPTION_MSG_IF_FAILED(m_Device->CreateDepthStencilState(&dsDesc, &m_DepthStencilState),
		//	"Depth Stencil State creation failed!", m_DXGIInfoManager.GetMessages());
		//m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState.Get(), 1u);
		
		//Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencil = nullptr;
		//D3D11_TEXTURE2D_DESC depthDesc = {};
		//depthDesc.Width = clientRect.right - clientRect.left;
		//depthDesc.Height = clientRect.bottom - clientRect.top;
		//depthDesc.MipLevels = 1u;
		//depthDesc.ArraySize = 1u;
		//depthDesc.Format = DXGI_FORMAT_D32_FLOAT;
		//depthDesc.SampleDesc.Count = 1u;
		//depthDesc.SampleDesc.Quality = 0u;
		//depthDesc.Usage = D3D11_USAGE_DEFAULT;
		//depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		//THROW_D3D_EXCEPTION_MSG_IF_FAILED(m_Device->CreateTexture2D(&depthDesc, nullptr, &depthStencil),
		//	"m_Device->CreateTexture2D failed!", m_DXGIInfoManager.GetMessages());
		
		
		//D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
		//depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
		//depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		//depthStencilViewDesc.Texture2D.MipSlice = 0u;
		//THROW_D3D_EXCEPTION_MSG_IF_FAILED(
		//	m_Device->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, &m_DepthStencilView),
		//	"m_Device->CreateTexture2D failed!", m_DXGIInfoManager.GetMessages()
		//);
		
		
		//m_DeviceContext->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());
		//
		//D3D11_VIEWPORT viewPort = { 0 };
		//viewPort.Width = clientRect.right - clientRect.left;
		//viewPort.Height = clientRect.bottom - clientRect.top;
		//viewPort.MinDepth = 0.0f;
		//viewPort.MaxDepth = 1.0f;
		//m_DeviceContext->RSSetViewports(1, &viewPort);
	}
	
	void SwapChain::SwapBuffers(bool vsync) const noexcept
	{
		m_SwapChain->Present(vsync, 0);
	}
}