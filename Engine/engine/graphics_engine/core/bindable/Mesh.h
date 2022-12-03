#pragma once
#include "engine/graphics_engine/core/bindable/Bindable.h"
#include "engine/graphics_engine/core/bindable/VertexBuffer.h"
#include "engine/graphics_engine/core/bindable/IndexBuffer.h"


#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>


namespace engine::graphics::core {
	class Mesh : public Bindable
	{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

		void Bind() const noexcept override;

		const VertexBuffer& GetVertexBuffer() const noexcept;
		const IndexBuffer& GetIndexBuffer() const noexcept;

	private:
		VertexBuffer m_VBO;
		IndexBuffer m_IBO;
	};
}