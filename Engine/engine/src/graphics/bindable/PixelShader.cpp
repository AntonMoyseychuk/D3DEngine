#include "PixelShader.h"

#include <d3dcompiler.h>
#include <stdarg.h>

namespace engine::graphics {
    PixelShader::PixelShader(const std::wstring& filepath)
        : Bindable(), m_Filepath(filepath)
    {
        OnCreate();
    }

    void PixelShader::Bind() const noexcept
    {
        D3DDevice::Get().GetImmediateDeviceContext()->PSSetShader(m_PS.Get(), nullptr, 0);
    }

    void PixelShader::OnCreate() const
    {
        Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
        if (FAILED(D3DX11CompileFromFile(m_Filepath.c_str(), nullptr, nullptr,
            "main", "ps_4_0", 0, 0, nullptr, &m_PsBinary, &errorBlob, nullptr)))
        {
            if (errorBlob == nullptr) {
                THROW_EXCEPTION_IF_LOGIC_ERROR(true, "PIXEL SHADER", 
                    "Invalid pixel shader filepath: " + util::StringParser::ToString(m_Filepath));
            }
            else {
                std::string error((char*)errorBlob->GetBufferPointer());
                THROW_EXCEPTION_IF_LOGIC_ERROR(true, "PIXEL SHADER", error);
            }
        }

        if (FAILED(D3DDevice::Get().GetDevice()->CreatePixelShader(m_PsBinary->GetBufferPointer(),
            m_PsBinary->GetBufferSize(), nullptr, &m_PS))) {
            THROW_EXCEPTION_IF_LOGIC_ERROR(true, "PIXEL SHADER", "Pixel shader creation failed!");
        }
    }
}