#pragma once
#include <d3dx11.h>
#include <wrl.h>

#include "Bindable.h"


namespace graphics_engine::core {
	class Buffer : public Bindable
	{
	public:
		Buffer() = default;
		Buffer(size_t size);

		ID3D11Buffer* GetID() const;
		virtual const char* GetType() const noexcept = 0;

	protected:

		virtual void OnCreateID(const void* data) const;

	protected:
		mutable Microsoft::WRL::ComPtr<ID3D11Buffer> m_ID = nullptr;
		mutable D3D11_BUFFER_DESC m_BufferDesc = { 0 };

		uint32_t m_Size = 0;
	};
}