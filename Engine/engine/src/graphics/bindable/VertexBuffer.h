#pragma once
#include "Buffer.h"
#include "engine/src/graphics/Vertex.h"

namespace engine::graphics {
	class VertexBuffer : public Buffer<engine::graphics::Vertex>
	{
	public:
		VertexBuffer(const Graphics& graphics, const std::vector<engine::graphics::Vertex>& vertices);
		void Bind() const noexcept override;

		uint32_t GetVertCount() const;

		const char* GetType() const noexcept override
		{
			return "Vertex";
		}
	};
}