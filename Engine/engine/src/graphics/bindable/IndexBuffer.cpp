#include "IndexBuffer.h"

namespace engine::graphics {
	IndexBuffer::IndexBuffer(const Graphics& graphics, const std::vector<uint32_t>& indices)
		: Buffer(graphics, indices.size() * sizeof(uint32_t))
	{
		THROW_EXCEPTION_IF_LOGIC_ERROR(indices.empty(), std::string(this->GetType()) + " BUFFER", "\"indices\" argument is empty!");

		m_BufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;

		OnCreateID(indices.data());
		Bind();
	}

	void IndexBuffer::Bind() const noexcept
	{
		m_Graphics.GetDeviceContext()->IASetIndexBuffer(m_ID.Get(), DXGI_FORMAT_R32_UINT, 0);
	}

	uint32_t IndexBuffer::GetIndexCount() const
	{
		return m_Size / sizeof(uint32_t);
	}

	const char* IndexBuffer::GetType() const noexcept
	{
		return "Index";
	}
}