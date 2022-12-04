#include "Texture.h"
#include "engine/utility/exception/ExeptionMacros.h"

namespace engine::graphics::core {
	Texture::Texture(const wchar_t* filepath)
		: Resource(filepath), Bindable()
	{
		OnCreate();
	}

	void Texture::Bind() const noexcept
	{
		D3DDevice::Get().GetImmediateDeviceContext()->PSSetShaderResources(0, 1, m_ID.GetAddressOf());
		D3DDevice::Get().GetImmediateDeviceContext()->PSSetSamplers(0, 1, m_SamplerState.GetAddressOf());
	}

	void Texture::OnCreate() const
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFileW(D3DDevice::Get().GetDevice(), m_Fullpath.c_str(), NULL, NULL, &m_ID, NULL);
		THROW_EXCEPTION_IF_HRESULT_ERROR(hr, "TEXTURE", "Shader resource view creation from file failed!");

		D3D11_SAMPLER_DESC sampDesc;
		memset(&sampDesc, 0, sizeof(sampDesc));

		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		hr = D3DDevice::Get().GetDevice()->CreateSamplerState(&sampDesc, &m_SamplerState);
		THROW_EXCEPTION_IF_HRESULT_ERROR(hr, "TEXTURE", "Sampler state creation failed!");
	}
}