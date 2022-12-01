#pragma once
#include <d3d11.h>
#include <wrl.h>

namespace engine::graphics {
	class D3DDevice final
	{
		friend class Graphics;
		friend class SwapChain;
	public:
		static D3DDevice& Get();

		ID3D11Device* GetDeviceD3D11();
		ID3D11DeviceContext* GetDeviceContextD3D11();

		IDXGIFactory* GetFactoryDXGI();

	private:
		D3DDevice();

	private:
		D3D_FEATURE_LEVEL m_FeatureLevel;
		Microsoft::WRL::ComPtr<ID3D11Device> m_D3DDevice = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_ImmediateContext = nullptr;
		
		Microsoft::WRL::ComPtr<IDXGIFactory> m_DXGIFactory = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> m_DXGIAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIDevice> m_DXGIDevice = nullptr;
	};
}