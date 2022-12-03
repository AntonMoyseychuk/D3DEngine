#include "IndexBuffer.h"
#include "engine/utility/exception/ExeptionMacros.h"

namespace graphics_engine::core {
	IndexBuffer::IndexBuffer(const std::vector<uint32_t>& indices)
		: Buffer(indices.size() * sizeof(uint32_t))
	{
		THROW_EXCEPTION_IF_LOGIC_ERROR(indices.empty(), std::string(this->GetType()) + " BUFFER", "\"indices\" argument is empty!");

		m_BufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;

		OnCreateID(indices.data());
		Bind();
	}

	void IndexBuffer::Bind() const noexcept
	{
		D3DDevice::Get().GetImmediateDeviceContext()->IASetIndexBuffer(m_ID.Get(), DXGI_FORMAT_R32_UINT, 0);
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