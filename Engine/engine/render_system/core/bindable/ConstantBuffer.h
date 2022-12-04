#pragma once
#include "Buffer.h"
#include "engine/utility/exception/ExeptionMacros.h"

namespace engine::graphics::core {
    template<typename T>
    class ConstantBuffer : public Buffer
    {
    public:
        ConstantBuffer() : Buffer()
        {
            this->m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
            this->m_BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            this->m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            this->m_BufferDesc.MiscFlags = 0;
            this->m_BufferDesc.StructureByteStride = 0;
            this->m_BufferDesc.ByteWidth = sizeof(T);

            HRESULT hr = D3DDevice::Get().GetDevice()->CreateBuffer(&this->m_BufferDesc, nullptr, &this->m_ID);
            THROW_EXCEPTION_IF_HRESULT_ERROR(hr, std::string(this->GetType()) + " BUFFER", 
                std::string(this->GetType()) + " Buffer creation failed!");
        }

        ConstantBuffer(const T& data) : Buffer(sizeof(data))
        {
            this->m_BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
            this->m_BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            this->m_BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            this->m_BufferDesc.MiscFlags = 0;
            this->m_BufferDesc.StructureByteStride = 0;

            this->OnCreateID(&data);
        }

        void Update(const T& data) const
        {
            D3D11_MAPPED_SUBRESOURCE msr;
            HRESULT hr = D3DDevice::Get().GetImmediateDeviceContext()->Map(this->m_ID.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr);
            THROW_EXCEPTION_IF_HRESULT_ERROR(hr, std::string(this->GetType()) + " BUFFER", "Can't get constant buffer data from GPU!");
            memcpy(msr.pData, &data, sizeof(data));
            D3DDevice::Get().GetImmediateDeviceContext()->Unmap(this->m_ID.Get(), 0u);
        }

        const char* GetType() const noexcept override { return "Constant"; }
    };

    template<typename T>
    class VSConstantBuffer : public ConstantBuffer<T>
    {
    public:
        using ConstantBuffer<T>::ConstantBuffer;

        const char* GetType() const noexcept override { return "Vertex Shader Constant"; }

        void Bind() const noexcept  override
        {
            D3DDevice::Get().GetImmediateDeviceContext()->VSSetConstantBuffers(0u, 1u, this->m_ID.GetAddressOf());
        }
    };

    template<typename T>
    class PSConstantBuffer : public ConstantBuffer<T>
    {
    public:
        using ConstantBuffer<T>::ConstantBuffer;

        const char* GetType() const noexcept override { return "Pixel Shader Constant"; }

        void Bind() const noexcept override
        {
            D3DDevice::Get().GetImmediateDeviceContext()->PSSetConstantBuffers(0u, 1u, this->m_ID.GetAddressOf());
        }
    };
}