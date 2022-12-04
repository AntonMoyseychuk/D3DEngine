#include "RenderSystem.h"
#include "D3DDevice.h"

#include "engine/render_system/core/drawable/Model.h"
#include "engine/render_system/core/bindable/VertexShader.h"
#include "engine/render_system/core/bindable/PixelShader.h"

#include "engine/utility/exception/ExeptionMacros.h"
#include "engine/utility/winapi/WinAPI.h"


namespace engine::graphics::core {
	RenderSystem& RenderSystem::Get() noexcept
	{
		static RenderSystem gfx;
		return gfx;
	}

	RenderSystem::RenderSystem()
	{
		auto devicePtr = D3DDevice::Get().GetDevice();

		D3D11_RASTERIZER_DESC rastDesc;
		memset(&rastDesc, 0, sizeof(rastDesc));
		rastDesc.CullMode = D3D11_CULL_FRONT;
		rastDesc.DepthClipEnable = true;
		rastDesc.FillMode = D3D11_FILL_SOLID;
		if (devicePtr != nullptr) devicePtr->CreateRasterizerState(&rastDesc, &m_CullStateFront);

		rastDesc.CullMode = D3D11_CULL_BACK;
		devicePtr->CreateRasterizerState(&rastDesc, &m_CullStateBackward);
	}

	void RenderSystem::DrawIndexed(uint32_t count) const noexcept
	{
		D3DDevice::Get().GetImmediateDeviceContext()->DrawIndexed(count, 0, 0);
	}

	void RenderSystem::Draw(uint32_t count) const noexcept
	{
		D3DDevice::Get().GetImmediateDeviceContext()->Draw(count, 0);
	}

	void RenderSystem::DrawModel(const Model* model, const VertexShader* vs, const PixelShader* ps)
	{
		vs->Bind();
		ps->Bind();
		for (auto& mesh : model->GetMeshes()) {
			mesh.Bind();
			this->DrawIndexed(mesh.GetIndexBuffer().GetIndexCount());
		}
	}

	void core::RenderSystem::SetRasterizerState(bool cullFront) const noexcept
	{
		D3DDevice::Get().GetImmediateDeviceContext()->RSSetState(cullFront ? m_CullStateFront.Get() : m_CullStateBackward.Get());
	}

	DirectX::XMMATRIX RenderSystem::GetProjectionMatrix() const noexcept
	{
		return m_ProjectionMatrix;
	}

	void RenderSystem::SetProjectionMatrix(const DirectX::XMMATRIX& proj) noexcept
	{
		m_ProjectionMatrix = proj;
	}
}