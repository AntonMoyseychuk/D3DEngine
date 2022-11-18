#pragma once
#include <d3dx11.h>
#include <vector>
#include <wrl.h>

#include "Bindable.h"
#include "engine/src/utility/exception/D3DException.h"

namespace engine::graphics {
	template <typename T>
	class Buffer : public Bindable
	{
	public:
		Buffer(const Graphics& gfx)
			: Bindable(gfx) 
		{
		}

		Buffer(const Graphics& gfx, size_t size)
			: Bindable(gfx), m_ID(nullptr), m_BufferDesc({0}), m_Size(size)
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
			if (data == nullptr) {
				THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(E_INVALIDARG, "\"data\" argument is nullptr!");
			}

			D3D11_SUBRESOURCE_DATA gpuBuffer = { 0 };
			gpuBuffer.pSysMem = data;

			HRESULT hr = GetGraphics().GetDevice()->CreateBuffer(&this->m_BufferDesc, &gpuBuffer, &this->m_ID);
			if (FAILED(hr)) {
				THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(hr, (std::string(this->GetType()) + " Buffer creation failed!").c_str());
			}
		}

	protected:
		mutable Microsoft::WRL::ComPtr<ID3D11Buffer> m_ID = nullptr;
		mutable D3D11_BUFFER_DESC m_BufferDesc = { 0 };

		uint32_t m_Size = 0;
	};
}