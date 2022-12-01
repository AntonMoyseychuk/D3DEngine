#include "Graphics.h"
#include "D3DDevice.h"

#include "engine/src/utility/exception/ExeptionMacros.h"
#include "engine/src/utility/winapi/WinAPI.h"


namespace engine::graphics {
	Graphics& Graphics::Get() noexcept
	{
		static Graphics gfx;
		return gfx;
	}

	void Graphics::Init(SwapChain& swapChain)
	{
		THROW_EXCEPTION_IF_LOGIC_ERROR(swapChain.m_SwapChain == nullptr, "GRAPHICS", 
			"Swap chain is not initialized, it must be inialized before graphics initialization");


		Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer = nullptr;
		THROW_EXCEPTION_IF_HRESULT_ERROR(swapChain.GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer),
			"GRAPHICS", "m_SwapChain->GetBuffer failed!");
		
		
		THROW_EXCEPTION_IF_HRESULT_ERROR(D3DDevice::Get().GetDevice()->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_RenderTargetView),
			"GRAPHICS", "Render Target View creation failed!");
		
		
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = true;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState = nullptr;
		THROW_EXCEPTION_IF_HRESULT_ERROR(D3DDevice::Get().GetDevice()->CreateDepthStencilState(&dsDesc, &m_DepthStencilState), 
			"GRAPHICS", "Depth Stencil State creation failed!");
		D3DDevice::Get().GetImmediateDeviceContext()->OMSetDepthStencilState(m_DepthStencilState.Get(), 1u);
		
		
		RECT clientRect = { 0 };
		GetClientRect(GetForegroundWindow(), &clientRect);
		
		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencil = nullptr;
		D3D11_TEXTURE2D_DESC depthDesc = {};
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
			"GRAPHICS", "m_Device->CreateTexture2D failed!");
		
		
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
		depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0u;
		THROW_EXCEPTION_IF_HRESULT_ERROR(D3DDevice::Get().GetDevice()->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, &m_DepthStencilView),
			"GRAPHICS", "m_Device->CreateTexture2D failed!");
		
		D3DDevice::Get().GetImmediateDeviceContext()->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());
		
		D3D11_VIEWPORT viewPort = { 0 };
		viewPort.Width = clientRect.right - clientRect.left;
		viewPort.Height = clientRect.bottom - clientRect.top;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		D3DDevice::Get().GetImmediateDeviceContext()->RSSetViewports(1, &viewPort);
		
		
		D3D11_RASTERIZER_DESC rastDesc;
		memset(&rastDesc, 0, sizeof(rastDesc));
		rastDesc.CullMode = D3D11_CULL_FRONT;
		rastDesc.DepthClipEnable = true;
		rastDesc.FillMode = D3D11_FILL_SOLID;
		D3DDevice::Get().GetDevice()->CreateRasterizerState(&rastDesc, &m_CullStateFront);
		
		rastDesc.CullMode = D3D11_CULL_BACK;
		D3DDevice::Get().GetDevice()->CreateRasterizerState(&rastDesc, &m_CullStateBackward);
	}

	void Graphics::ClearBuffers(float r, float g, float b, float a) const noexcept
	{
		auto immContext = D3DDevice::Get().GetImmediateDeviceContext();
		
		float color[] = { r, g, b, a };
		immContext->ClearRenderTargetView(m_RenderTargetView.Get(), color);
		immContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
	}

	void Graphics::DrawIndexed(uint32_t count) const noexcept
	{
		D3DDevice::Get().GetImmediateDeviceContext()->DrawIndexed(count, 0, 0);
	}

	void Graphics::Draw(uint32_t count) const noexcept
	{
		D3DDevice::Get().GetImmediateDeviceContext()->Draw(count, 0);
	}

	void graphics::Graphics::SetRasterizerState(bool cullFront) const noexcept
	{
		D3DDevice::Get().GetImmediateDeviceContext()->RSSetState(cullFront ? m_CullStateFront.Get() : m_CullStateBackward.Get());
	}

	DirectX::XMMATRIX Graphics::GetProjection() const noexcept
	{
		return m_ProjectionMatrix;
	}

	void Graphics::SetProjectionMatrix(const DirectX::XMMATRIX& proj) noexcept
	{
		m_ProjectionMatrix = proj;
	}
}