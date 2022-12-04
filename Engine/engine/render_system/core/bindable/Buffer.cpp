#include "Buffer.h"
#include "engine/utility/exception/ExeptionMacros.h"

namespace engine::graphics::core {
	Buffer::Buffer(size_t size)
		: Bindable(), m_ID(nullptr), m_BufferDesc({ 0 }), m_Size(size)
	{
		m_BufferDesc.ByteWidth = size;
		m_BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		m_BufferDesc.CPUAccessFlags = 0;
	}

	ID3D11Buffer* Buffer::GetID() const 
	{ 
		return m_ID.Get(); 
	}
	
	void Buffer::OnCreateID(const void* data) const
	{
		THROW_EXCEPTION_IF_LOGIC_ERROR(data == nullptr, "BUFFER", "\"data\" argument is nullptr!");

		D3D11_SUBRESOURCE_DATA gpuBuffer = { 0 };
		gpuBuffer.pSysMem = data;

		HRESULT hr = D3DDevice::Get().GetDevice()->CreateBuffer(&this->m_BufferDesc, &gpuBuffer, &this->m_ID);
		THROW_EXCEPTION_IF_HRESULT_ERROR(hr, " BASE BUFFER", "Base buffer creation failed!");
	}
}