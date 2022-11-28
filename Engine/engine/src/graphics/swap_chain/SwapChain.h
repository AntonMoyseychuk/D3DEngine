#pragma once
#include "Graphics.h"

namespace engine::graphics {
	class DeviceContext;

	class SwapChain
	{
	public:
		SwapChain(HWND windowHandle, uint32_t width, uint32_t height);

		void SwapBuffers(bool vsync) const noexcept;

	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain = nullptr;

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState = nullptr;

	private:
		friend class DeviceContext;
	};
}