#pragma once
#include "engine/graphics_engine/core/bindable/Bindable.h"

namespace graphics_engine::core {
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