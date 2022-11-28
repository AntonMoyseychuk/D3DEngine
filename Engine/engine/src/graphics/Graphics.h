#pragma once

#include "engine/src/graphics/camera/Camera.h"

#include <d3dx11.h>
#include <DirectXMath.h>
#include <wrl.h>

namespace engine::graphics {
	class Graphics
	{
	public:
		typedef HWND window_id;
		Camera Camera;

	public:
		Graphics(window_id id);
		~Graphics() = default;

		Graphics(const Graphics&) = delete;
		Graphics& operator=(const Graphics&) = delete;

		inline ID3D11Device* GetDevice() const noexcept { return m_Device.Get(); }
		inline IDXGISwapChain* GetSwapChain() const noexcept { return m_SwapChain.Get(); }
		inline ID3D11DeviceContext* GetDeviceContext() const noexcept { return m_DeviceContext.Get(); }
		inline ID3D11RenderTargetView* GetRenderTargetView() const noexcept { return m_RenderTargetView.Get(); }

		void SwapBuffers() const noexcept;
		void ClearBuffers(float r, float g, float b) const noexcept;
		void DrawIndexed(uint32_t count) const noexcept;
		void Draw(uint32_t count) const noexcept;
		void SetRasterizerState(bool cullFront) const noexcept;

		void SetProjectionMatrix(const DirectX::XMMATRIX& proj) noexcept;
		DirectX::XMMATRIX GetProjection() const noexcept;

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device = nullptr;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext = nullptr;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState = nullptr;

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_CullStateFront = nullptr;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_CullStateBackward = nullptr;

		DirectX::XMMATRIX m_ProjectionMatrix;
	};
}