#include "TransformConstantBuffer.h"

namespace engine::graphics {
	TransformConstantBuffer::TransformConstantBuffer(const Graphics& gfx, const Drawable& parent)
		: Bindable(gfx), m_Parent(parent)
	{
		if (m_VSConstBuff == nullptr) {
			m_VSConstBuff = std::make_unique<VSConstantBuffer<Transform>>(
				gfx, 
				Transform{
					DirectX::XMMatrixTranspose(m_Parent.GetTransform()),
					DirectX::XMMatrixTranspose(m_Graphics.Camera.GetViewMatrix()),
					DirectX::XMMatrixTranspose(m_Graphics.GetProjection())
				}
			);
		}
	}
	
	void TransformConstantBuffer::Bind() const noexcept
	{
		m_VSConstBuff->Update(Transform{
				DirectX::XMMatrixTranspose(m_Parent.GetTransform()),
				DirectX::XMMatrixTranspose(m_Graphics.Camera.GetViewMatrix()),
				DirectX::XMMatrixTranspose(m_Graphics.GetProjection())
			}
		);
		m_VSConstBuff->Bind();
	}

	std::unique_ptr<VSConstantBuffer<TransformConstantBuffer::Transform>> TransformConstantBuffer::m_VSConstBuff;
}