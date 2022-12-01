#include "PrimitiveTopology.h"

namespace engine::graphics {
	PrimitiveTopology::PrimitiveTopology(Type type)
		: Bindable(), m_Topology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(type))
	{
	}

	void PrimitiveTopology::Bind() const noexcept
	{
		D3DDevice::Get().GetDeviceContextD3D11()->IASetPrimitiveTopology(m_Topology);
	}
}