#pragma once
#include "D3DDevice.h"

#include <d3d11.h>
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

	private:
		SwapChain() = default;

		void Init(HWND windowID, D3DDevice& device);
		IDXGISwapChain* GetSwapChainDXGI() noexcept;

	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain = nullptr;
	};
}