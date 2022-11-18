#pragma once
#include "engine/src/graphics/bindable/Bindable.h"

namespace engine::graphics {
	class PrimitiveTopology : public Bindable
	{
	public:
		enum class Type : uint32_t
		{
			TRIANGLES = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			TRIANGLE_STRIP = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,

			LINES = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST,
			LINE_STRIP = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP,

			POINTS = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_POINTLIST,
		};

	public:
		PrimitiveTopology(const Graphics& gfx, Type type);
		void Bind() const noexcept override;

	protected:
		D3D11_PRIMITIVE_TOPOLOGY m_Topology;
	};
}