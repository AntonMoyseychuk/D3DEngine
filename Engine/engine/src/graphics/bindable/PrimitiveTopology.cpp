#include "PrimitiveTopology.h"

namespace engine::graphics {
	PrimitiveTopology::PrimitiveTopology(const Graphics& gfx, Type type)
		: Bindable(gfx), m_Topology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(type))
	{
	}

	void PrimitiveTopology::Bind() const noexcept
	{
		m_Graphics.GetDeviceContext()->IASetPrimitiveTopology(m_Topology);
	}
}