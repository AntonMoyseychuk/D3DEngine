#include "D3DDevice.h"
#include "engine/src/utility/exception/ExeptionMacros.h"
#include <stdint.h>

namespace engine::graphics {
	D3DDevice& D3DDevice::Get()
	{
		static D3DDevice device;
		return device;
	}

	D3DDevice::D3DDevice()
	{
		D3D_DRIVER_TYPE driverTypes[] = {
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE
		};
		uint32_t driverTypesCount = ARRAYSIZE(driverTypes);

		D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_11_0
		};
		uint32_t featureLevelsCount = ARRAYSIZE(featureLevels);

		HRESULT hr;
		for (const auto& driverType : driverTypes) {
			hr = D3D11CreateDevice(nullptr, driverType, nullptr, 0, featureLevels, featureLevelsCount, D3D11_SDK_VERSION,
				&m_D3DDevice, &m_FeatureLevel, &m_ImmediateContext);

			if (SUCCEEDED(hr)) {
				break;
			}
		}

		THROW_EXCEPTION_IF_HRESULT_ERROR(hr, "DIRECT3D DEVICE", "Direct3D device creation failed");

		hr = m_D3DDevice->QueryInterface(__uuidof(IDXGIDevice), &m_DXGIDevice);
		THROW_EXCEPTION_IF_HRESULT_ERROR(hr, "DIRECT3D DEVICE", "Can't get IDXGIDevice");
		hr = m_DXGIDevice->GetParent(__uuidof(IDXGIAdapter), &m_DXGIAdapter);
		THROW_EXCEPTION_IF_HRESULT_ERROR(hr, "DIRECT3D DEVICE", "Can't get IDXGIAdapter");
		hr = m_DXGIAdapter->GetParent(__uuidof(IDXGIFactory), &m_DXGIFactory);
		THROW_EXCEPTION_IF_HRESULT_ERROR(hr, "DIRECT3D DEVICE", "Can't get IDXGIFactory");
	}

	ID3D11Device* D3DDevice::GetDeviceD3D11()
	{
		return m_D3DDevice.Get();
	}

	ID3D11DeviceContext* D3DDevice::GetDeviceContextD3D11()
	{
		return m_ImmediateContext.Get();
	}
	IDXGIFactory* D3DDevice::GetFactoryDXGI()
	{
		return m_DXGIFactory.Get();
	}
}