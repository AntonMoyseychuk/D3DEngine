#pragma once
#include "engine/render_system/camera/Camera.h"

#include <d3dx11.h>
#include <DirectXMath.h>
#include <wrl.h>


namespace engine::graphics::core {
	class Model;
	class VertexShader;
	class PixelShader;

	class RenderSystem final
	{
	public:
		static RenderSystem& Get() noexcept;

	public:
		void DrawModel(const Model* model, const VertexShader* vs, const PixelShader* ps);
		void SetRasterizerState(bool cullFront) const noexcept;

		void SetProjectionMatrix(const DirectX::XMMATRIX& proj) noexcept;
		DirectX::XMMATRIX GetProjectionMatrix() const noexcept;

	private:
		RenderSystem();

		void Draw(uint32_t vertexCount) const noexcept;
		void DrawIndexed(uint32_t count) const noexcept;

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