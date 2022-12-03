#include "PrimitiveTopology.h"

namespace graphics_engine::core {
	PrimitiveTopology::PrimitiveTopology(Type type)
		: Bindable(), m_Topology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(type))
	{
	}

	void PrimitiveTopology::Bind() const noexcept
	{
		D3DDevice::Get().GetImmediateDeviceContext()->IASetPrimitiveTopology(m_Topology);
	}
}