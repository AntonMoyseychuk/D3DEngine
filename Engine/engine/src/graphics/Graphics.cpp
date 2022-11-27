#include "Graphics.h"

#include "engine/src/utility/winapi/WinAPI.h"
#include "engine/src/utility/exception/D3DException.h"


namespace engine::graphics {
	Graphics::Graphics(window_id id)
		: m_ProjectionMatrix(DirectX::XMMatrixIdentity()), Camera()
	{
		RECT clientRect = { 0 };
		GetClientRect(GetForegroundWindow(), &clientRect);

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
		swapChainDesc.OutputWindow = id;
		swapChainDesc.Windowed = true;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = 0;

		HRESULT D3D_OP_RESULT;

		THROW_D3D_EXCEPTION_MSG_IF_FAILED(D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			D3D11_CREATE_DEVICE_DEBUG,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&m_SwapChain,
			&m_Device,
			nullptr,
			&m_DeviceContext),
			"D3D11CreateDeviceAndSwapChain failed!", m_DXGIInfoManager.GetMessages()
		);

		Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer = nullptr;
		THROW_D3D_EXCEPTION_MSG_IF_FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer),
			"m_SwapChain->GetBuffer failed!", m_DXGIInfoManager.GetMessages());

		THROW_D3D_EXCEPTION_MSG_IF_FAILED(m_Device->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_RenderTargetView),
			"Render Target View creation failed!", m_DXGIInfoManager.GetMessages());


		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = true;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState = nullptr;
		THROW_D3D_EXCEPTION_MSG_IF_FAILED(m_Device->CreateDepthStencilState(&dsDesc, &m_DepthStencilState),
			"Depth Stencil State creation failed!", m_DXGIInfoManager.GetMessages());
		m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState.Get(), 1u);
		
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
		THROW_D3D_EXCEPTION_MSG_IF_FAILED(m_Device->CreateTexture2D(&depthDesc, nullptr, &depthStencil),
			"m_Device->CreateTexture2D failed!", m_DXGIInfoManager.GetMessages());


		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
		depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0u;
		THROW_D3D_EXCEPTION_MSG_IF_FAILED(
			m_Device->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, &m_DepthStencilView),
			"m_Device->CreateTexture2D failed!", m_DXGIInfoManager.GetMessages()
		);


		m_DeviceContext->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());

		D3D11_VIEWPORT viewPort = { 0 };
		viewPort.Width = clientRect.right - clientRect.left;
		viewPort.Height = clientRect.bottom - clientRect.top;
		viewPort.MinDepth = 0.0f;
		viewPort.MaxDepth = 1.0f;
		m_DeviceContext->RSSetViewports(1, &viewPort);


		D3D11_RASTERIZER_DESC rastDesc;
		memset(&rastDesc, 0, sizeof(rastDesc));
		rastDesc.CullMode = D3D11_CULL_FRONT;
		rastDesc.DepthClipEnable = true;
		rastDesc.FillMode = D3D11_FILL_SOLID;
		m_Device->CreateRasterizerState(&rastDesc, &m_CullStateFront);

		rastDesc.CullMode = D3D11_CULL_BACK;
		m_Device->CreateRasterizerState(&rastDesc, &m_CullStateBackward);
	}

	void Graphics::SwapBuffers() const noexcept
	{
		HRESULT D3D_OP_RESULT;
		if (FAILED(D3D_OP_RESULT = m_SwapChain->Present(1u, 0u))) {
			if (D3D_OP_RESULT == DXGI_ERROR_DEVICE_REMOVED) {
				throw ENGINE_D3D_DEVICE_REMOVED_EXCEPTION(m_Device->GetDeviceRemovedReason(), m_DXGIInfoManager.GetMessages());
			}
			else {
				THROW_D3D_EXCEPTION_MSG_IF_FAILED(D3D_OP_RESULT, "SwapBuffers failed!", m_DXGIInfoManager.GetMessages());
			}
		}
	}

	void Graphics::ClearBuffers(float r, float g, float b) const noexcept
	{
		float color[] = { r, g, b, 1.0f };
		m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), color);
		m_DeviceContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
	}

	void Graphics::DrawIndexed(uint32_t count) const noexcept
	{
		m_DeviceContext->DrawIndexed(count, 0, 0);
	}

	void Graphics::Draw(uint32_t count) const noexcept
	{
		m_DeviceContext->Draw(count, 0);
	}

	void graphics::Graphics::SetRasterizerState(bool cullFront) const noexcept
	{
		m_DeviceContext->RSSetState(cullFront ? m_CullStateFront.Get() : m_CullStateBackward.Get());
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