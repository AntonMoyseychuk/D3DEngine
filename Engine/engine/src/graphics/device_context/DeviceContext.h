#pragma once
#include <d3dx11.h>
#include <stdint.h>
#include <wrl.h>

namespace engine::graphics {
	class Graphics;
	class SwapChain;

	class DeviceContext
	{
	public:
		DeviceContext();

	public:
		void ClearBuffers(const SwapChain& swapChain, float r, float g, float b, float a) const noexcept;
		void DrawIndexed(uint32_t count) const noexcept;
		void Draw(uint32_t vertexCount) const noexcept;
		void SetRasterizerState(bool cullFront) const noexcept;

	private:
		Microsoft::WRL::Details::ComPtrRef<Microsoft::WRL::ComPtr<ID3D11DeviceContext>> GetAddresOfDeviceContextForInit();

	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext = nullptr;

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_CullStateFront = nullptr;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_CullStateBackward = nullptr;

	private:
		friend class Graphics;
	};
}