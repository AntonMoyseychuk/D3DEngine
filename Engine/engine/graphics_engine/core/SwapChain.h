#pragma once
#include "D3DDevice.h"

#include <memory>
#include <d3d11.h>
#include <stdint.h>
#include <wrl.h>

namespace graphics_engine::window {
	class Window;
}

namespace graphics_engine::core {
	class SwapChain final
	{
		friend class graphics_engine::window::Window;

	public:
		IDXGISwapChain* GetSwapChain() noexcept;

	private:
		SwapChain(HWND windowID, uint32_t contextWidth, uint32_t contextHeight);
		
		void _ClearBuffers(float r, float g, float b, float a = 1.0f) const noexcept;
		void _SwapBuffers(bool vsync) const;

	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain = nullptr;

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState = nullptr;
	};
}