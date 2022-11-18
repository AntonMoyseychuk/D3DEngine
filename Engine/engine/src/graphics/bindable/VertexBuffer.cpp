#include "VertexBuffer.h"

namespace engine::graphics {
	VertexBuffer::VertexBuffer(const Graphics& graphics, const std::vector<Vertex>& vertices)
		: Buffer<Vertex>::Buffer(graphics, vertices.size() * sizeof(Vertex))
	{
		if (vertices.empty()) {
			THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(E_INVALIDARG, "\"verticies\" is empty!");
		}

		this->m_BufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;

		this->OnCreateID(vertices.data());
		Bind();
	}

	void VertexBuffer::Bind() const noexcept
	{
		uint32_t stride = sizeof(Vertex);
		uint32_t offset = 0u;
		this->m_Graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, this->m_ID.GetAddressOf(), &stride, &offset);
	}

	uint32_t VertexBuffer::GetVertCount() const
	{
		return this->m_Size / sizeof(Vertex);
	}
}