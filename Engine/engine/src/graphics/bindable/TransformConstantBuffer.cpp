#include "TransformConstantBuffer.h"
#include "engine/src/graphics/Graphics.h"

namespace engine::graphics {
	TransformConstantBuffer::TransformConstantBuffer(const Drawable& parent)
		: Bindable(), m_Parent(parent)
	{
		if (m_VSConstBuff == nullptr) {
			m_VSConstBuff = std::make_unique<VSConstantBuffer<Transform>>(
				Transform{
					DirectX::XMMatrixTranspose(m_Parent.GetTransform()),
					DirectX::XMMatrixTranspose(Graphics::Get().Camera.GetViewMatrix()),
					DirectX::XMMatrixTranspose(Graphics::Get().GetProjectionMatrix())
				}
			);
		}
	}
	
	void TransformConstantBuffer::Bind() const noexcept
	{
		m_VSConstBuff->Update(Transform{
				DirectX::XMMatrixTranspose(m_Parent.GetTransform()),
				DirectX::XMMatrixTranspose(Graphics::Get().Camera.GetViewMatrix()),
				DirectX::XMMatrixTranspose(Graphics::Get().GetProjectionMatrix())
			}
		);
		m_VSConstBuff->Bind();
	}

	std::unique_ptr<VSConstantBuffer<TransformConstantBuffer::Transform>> TransformConstantBuffer::m_VSConstBuff;
}