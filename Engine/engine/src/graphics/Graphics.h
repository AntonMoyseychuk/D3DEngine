#pragma once

#include "engine/src/graphics/camera/Camera.h"

#include <d3dx11.h>
#include <DirectXMath.h>
#include <wrl.h>

namespace engine::graphics {
	class Graphics final
	{
		friend class window::Window;

	public:
		static Graphics& Get() noexcept;

		void ClearBuffers(float r, float g, float b, float a = 1.0f) const noexcept;
		void DrawIndexed(uint32_t count) const noexcept;
		void Draw(uint32_t vertexCount) const noexcept;
		void SetRasterizerState(bool cullFront) const noexcept;

		void SetProjectionMatrix(const DirectX::XMMATRIX& proj) noexcept;
		DirectX::XMMATRIX GetProjection() const noexcept;

	private:
		void Init(SwapChain& swapChain);

	private:
		Graphics() = default;

		Graphics(const Graphics&) = delete;
		Graphics& operator=(const Graphics&) = delete;

	public:
		Camera Camera;

	private:
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState = nullptr;

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_CullStateFront = nullptr;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_CullStateBackward = nullptr;

		DirectX::XMMATRIX m_ProjectionMatrix = DirectX::XMMatrixIdentity();
	};
}