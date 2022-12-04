#pragma once
#include <vector>

#include "Buffer.h"
#include "engine/render_system/core/Vertex.h"

namespace engine::graphics::core {
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(const std::vector<graphics::core::Vertex>& vertices);
		void Bind() const noexcept override;

		uint32_t GetVertCount() const;

		const char* GetType() const noexcept override;
	};
}