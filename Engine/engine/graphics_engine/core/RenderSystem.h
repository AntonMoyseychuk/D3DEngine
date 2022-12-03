#pragma once
#include "engine/camera/Camera.h"

#include <d3dx11.h>
#include <DirectXMath.h>
#include <wrl.h>


namespace graphics_engine::core {
	class RenderSystem final
	{
	public:
		static RenderSystem& Get() noexcept;

	public:
		void Draw(uint32_t vertexCount) const noexcept;
		void DrawIndexed(uint32_t count) const noexcept;
		void SetRasterizerState(bool cullFront) const noexcept;

		void SetProjectionMatrix(const DirectX::XMMATRIX& proj) noexcept;
		DirectX::XMMATRIX GetProjectionMatrix() const noexcept;

	private:
		RenderSystem();

		RenderSystem(const RenderSystem&) = delete;
		RenderSystem& operator=(const RenderSystem&) = delete;

	public:
		Camera Camera;

	private:
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_CullStateFront = nullptr;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_CullStateBackward = nullptr;

		DirectX::XMMATRIX m_ProjectionMatrix = DirectX::XMMatrixIdentity();
	};
}