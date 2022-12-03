#pragma once
#include <d3dx11.h>
#include <vector>
#include <wrl.h>

#include "Bindable.h"
#include "engine/utility/exception/ExeptionMacros.h"

namespace graphics_engine::core {
	template <typename T>
	class Buffer : public Bindable
	{
	public:
		Buffer() = default;

		Buffer(size_t size)
			: Bindable(), m_ID(nullptr), m_BufferDesc({0}), m_Size(size)
		{
			m_BufferDesc.ByteWidth = size;
			m_BufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
			m_BufferDesc.CPUAccessFlags = 0;
		}

		inline ID3D11Buffer* GetID() const { return m_ID.Get(); }
		virtual const char* GetType() const noexcept = 0;

	protected:

		virtual void OnCreateID(const T* data) const 
		{
			THROW_EXCEPTION_IF_LOGIC_ERROR(data == nullptr, "BUFFER", "\"data\" argument is nullptr!");

			D3D11_SUBRESOURCE_DATA gpuBuffer = { 0 };
			gpuBuffer.pSysMem = data;

			HRESULT hr = D3DDevice::Get().GetDevice()->CreateBuffer(&this->m_BufferDesc, &gpuBuffer, &this->m_ID);
			THROW_EXCEPTION_IF_HRESULT_ERROR(hr, " BASE BUFFER", "Base buffer creation failed!");
		}

	protected:
		mutable Microsoft::WRL::ComPtr<ID3D11Buffer> m_ID = nullptr;
		mutable D3D11_BUFFER_DESC m_BufferDesc = { 0 };

		uint32_t m_Size = 0;
	};
}