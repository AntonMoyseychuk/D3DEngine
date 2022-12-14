#pragma once
#include "engine/render_system/core/bindable/Bindable.h"

namespace engine::graphics::core {
	class PrimitiveTopology : public Bindable
	{
	public:
		enum class Type
		{
			TRIANGLES = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			TRIANGLE_STRIP = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,

			LINES = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST,
			LINE_STRIP = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP,

			POINTS = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_POINTLIST,
		};

	public:
		PrimitiveTopology(Type type);
		void Bind() const noexcept override;

	protected:
		D3D11_PRIMITIVE_TOPOLOGY m_Topology;
	};
}