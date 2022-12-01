#include "SwapChain.h"
#include "engine/src/utility/exception/ExeptionMacros.h"

namespace engine::graphics {
	IDXGISwapChain* SwapChain::GetSwapChain() noexcept
	{
		return m_SwapChain.Get();
	}

	void SwapChain::Init(HWND windowID, D3DDevice& device)
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
		swapChainDesc.BufferDesc.Width = 0;
		swapChainDesc.BufferDesc.Height = 0;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = windowID;
		swapChainDesc.Windowed = true;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = 0;

		HRESULT hr = device.m_DXGIFactory->CreateSwapChain(device.m_D3DDevice.Get(), &swapChainDesc, &m_SwapChain);
		THROW_EXCEPTION_IF_HRESULT_ERROR(hr, "SWAP CHAIN", "swap chain creation failed");
	}
}