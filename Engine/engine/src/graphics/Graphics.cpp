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

	void Graphics::Init()
	{
		D3D11_RASTERIZER_DESC rastDesc;
		memset(&rastDesc, 0, sizeof(rastDesc));
		rastDesc.CullMode = D3D11_CULL_FRONT;
		rastDesc.DepthClipEnable = true;
		rastDesc.FillMode = D3D11_FILL_SOLID;
		D3DDevice::Get().GetDevice()->CreateRasterizerState(&rastDesc, &m_CullStateFront);
		
		rastDesc.CullMode = D3D11_CULL_BACK;
		D3DDevice::Get().GetDevice()->CreateRasterizerState(&rastDesc, &m_CullStateBackward);
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

	DirectX::XMMATRIX Graphics::GetProjectionMatrix() const noexcept
	{
		return m_ProjectionMatrix;
	}

	void Graphics::SetProjectionMatrix(const DirectX::XMMATRIX& proj) noexcept
	{
		m_ProjectionMatrix = proj;
	}
}