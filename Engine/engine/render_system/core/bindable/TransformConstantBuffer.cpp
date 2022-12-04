#include "TransformConstantBuffer.h"
#include "engine/render_system/core/RenderSystem.h"

namespace engine::graphics::core {
	TransformConstantBuffer::TransformConstantBuffer(const Drawable& parent)
		: Bindable(), m_Parent(parent)
	{
		if (m_VSConstBuff == nullptr) {
			m_VSConstBuff = std::make_unique<VSConstantBuffer<Transform>>(
				Transform{
					DirectX::XMMatrixTranspose(m_Parent.GetTransform()),
					DirectX::XMMatrixTranspose(RenderSystem::Get().Camera.GetViewMatrix()),
					DirectX::XMMatrixTranspose(RenderSystem::Get().GetProjectionMatrix())
				}
			);
		}
	}
	
	void TransformConstantBuffer::Bind() const noexcept
	{
		m_VSConstBuff->Update(Transform{
				DirectX::XMMatrixTranspose(m_Parent.GetTransform()),
				DirectX::XMMatrixTranspose(RenderSystem::Get().Camera.GetViewMatrix()),
				DirectX::XMMatrixTranspose(RenderSystem::Get().GetProjectionMatrix())
			}
		);
		m_VSConstBuff->Bind();
	}

	std::unique_ptr<VSConstantBuffer<TransformConstantBuffer::Transform>> TransformConstantBuffer::m_VSConstBuff;
}