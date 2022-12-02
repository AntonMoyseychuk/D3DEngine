#pragma once
#include "D3DDevice.h"

#include <d3d11.h>
#include <stdint.h>
#include <wrl.h>

namespace engine::window {
	class Window;
}

namespace engine::graphics {
	class SwapChain final
	{
	public:
		friend class Graphics;
		friend class window::Window;

	public:
		IDXGISwapChain* GetSwapChain() noexcept;

	private:
		SwapChain() = default;
		void Init(HWND windowID, uint32_t clientStateWidth, uint32_t clientStateHeight);
		void ClearBuffers(float r, float g, float b, float a = 1.0f) const noexcept;

	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain = nullptr;

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState = nullptr;
	};
}