#include "Mesh.h"

namespace engine::graphics {
	Mesh::Mesh(const Graphics& gfx, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
		: Bindable(gfx), m_VBO(gfx, vertices), m_IBO(gfx, indices)
	{
	}

	void Mesh::Bind() const noexcept
	{
		m_VBO.Bind();
		m_IBO.Bind();
	}

	const VertexBuffer& Mesh::GetVertexBuffer() const noexcept
	{
		return m_VBO;
	}

	const IndexBuffer& Mesh::GetIndexBuffer() const noexcept
	{
		return m_IBO;
	}
}