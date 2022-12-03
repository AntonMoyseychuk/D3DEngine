#pragma once
#include "Buffer.h"
#include "engine/graphics_engine/core/Vertex.h"

namespace graphics_engine::core {
	class VertexBuffer : public Buffer<graphics_engine::core::Vertex>
	{
	public:
		VertexBuffer(const std::vector<graphics_engine::core::Vertex>& vertices);
		void Bind() const noexcept override;

		uint32_t GetVertCount() const;

		const char* GetType() const noexcept override
		{
			return "Vertex";
		}
	};
}