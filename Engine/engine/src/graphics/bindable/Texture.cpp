#include "Texture.h"
#include "engine/src/utility/exception/ExeptionMacros.h"

namespace engine::graphics {
	Texture::Texture(const wchar_t* filepath)
		: Bindable(), m_Filepath(filepath)
	{
		OnCreate();
	}

	void Texture::Bind() const noexcept
	{
		D3DDevice::Get().GetDeviceContextD3D11()->PSSetShaderResources(0, 1, m_ID.GetAddressOf());
		D3DDevice::Get().GetDeviceContextD3D11()->PSSetSamplers(0, 1, m_SamplerState.GetAddressOf());
	}

	void Texture::OnCreate() const
	{
		HRESULT hr = D3DX11CreateShaderResourceViewFromFileW(D3DDevice::Get().GetDeviceD3D11(), m_Filepath.c_str(), NULL, NULL, &m_ID, NULL);
		THROW_EXCEPTION_IF_HRESULT_ERROR(hr, "TEXTURE", "D3DX11CreateShaderResourceViewFromFile failed!");

		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));

		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		hr = D3DDevice::Get().GetDeviceD3D11()->CreateSamplerState(&sampDesc, &m_SamplerState);
		THROW_EXCEPTION_IF_HRESULT_ERROR(hr, "TEXTURE", "CreateSamplerState failed!");
	}
}