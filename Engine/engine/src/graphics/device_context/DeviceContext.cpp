#include "DeviceContext.h"
#include "SwapChain.h"

namespace engine::graphics {
	void DeviceContext::ClearBuffers(const SwapChain& swapChain, float r, float g, float b, float a) const noexcept
	{
		float color[] = { r, g, b, a };
		m_DeviceContext->ClearRenderTargetView(swapChain.m_RenderTargetView.Get(), color);
		//m_DeviceContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
	}

	void DeviceContext::DrawIndexed(uint32_t count) const noexcept
	{
		m_DeviceContext->DrawIndexed(count, 0, 0);
	}

	void DeviceContext::Draw(uint32_t vertexCount) const noexcept
	{
		m_DeviceContext->Draw(vertexCount, 0);
	}

	void DeviceContext::SetRasterizerState(bool cullFront) const noexcept
	{
		m_DeviceContext->RSSetState(cullFront ? m_CullStateFront.Get() : m_CullStateBackward.Get());
	}
	
	Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<ID3D11DeviceContext>> DeviceContext::GetAddresOfDeviceContextForInit()
	{
		return &m_DeviceContext;
	}
}