#pragma once
#include <d3d11.h>
#include <wrl.h>

namespace engine::graphics::core {
	class D3DDevice final
	{
	public:
		static D3DDevice& Get();

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetImmediateDeviceContext();
		IDXGIFactory* GetFactoryDXGI();

	private:
		D3DDevice();

		D3DDevice(const D3DDevice& device) = delete;
		D3DDevice& operator=(const D3DDevice& device) = delete;

	private:
		D3D_FEATURE_LEVEL m_FeatureLevel;
		Microsoft::WRL::ComPtr<ID3D11Device> m_D3DDevice = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_ImmediateContext = nullptr;
		
		Microsoft::WRL::ComPtr<IDXGIFactory> m_DXGIFactory = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> m_DXGIAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIDevice> m_DXGIDevice = nullptr;
	};
}