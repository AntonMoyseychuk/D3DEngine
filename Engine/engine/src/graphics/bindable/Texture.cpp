#include "Texture.h"
#include "engine/src/utility/exception/D3DException.h"

namespace engine::graphics {
	Texture::Texture(const Graphics& gfx, const wchar_t* filepath)
		: Bindable(gfx), m_Filepath(filepath)
	{
		OnCreate();
	}

	void Texture::Bind() const noexcept
	{
		m_Graphics.GetDeviceContext()->PSSetShaderResources(0, 1, m_ID.GetAddressOf());
		m_Graphics.GetDeviceContext()->PSSetSamplers(0, 1, m_SamplerState.GetAddressOf());
	}

	void Texture::OnCreate() const
	{
		if (FAILED(D3DX11CreateShaderResourceViewFromFile(m_Graphics.GetDevice(), m_Filepath.c_str(), NULL, NULL, &m_ID, NULL))) {
			THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(DXGI_ERROR_INVALID_CALL, "D3DX11CreateShaderResourceViewFromFile failed!");
		}

		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));

		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		if (FAILED(m_Graphics.GetDevice()->CreateSamplerState(&sampDesc, &m_SamplerState))) {
			THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(DXGI_ERROR_INVALID_CALL, "CreateSamplerState failed!");
		}
	}
}