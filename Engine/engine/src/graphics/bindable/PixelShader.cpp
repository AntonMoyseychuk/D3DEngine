#include "PixelShader.h"
#include "engine/src/utility/exception/D3DException.h"

#include <d3dcompiler.h>
#include <stdarg.h>

namespace engine::graphics {
    PixelShader::PixelShader(const Graphics& gfx, const std::wstring& filepath)
        : Bindable(gfx), m_Filepath(filepath)
    {
        OnCreate();
    }

    void PixelShader::Bind() const noexcept
    {
        m_Graphics.GetDeviceContext()->PSSetShader(m_PS.Get(), nullptr, 0);
    }

    void PixelShader::OnCreate() const
    {
        Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
        if (FAILED(D3DX11CompileFromFile(m_Filepath.c_str(), nullptr, nullptr,
            "main", "ps_4_0", 0, 0, nullptr, &m_PsBinary, &errorBlob, nullptr)))
        {
            if (errorBlob == nullptr) {
                THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(E_INVALIDARG,
                    ("Invalid pixel shader filepath: " + util::Parser::ToString(m_Filepath)).c_str());
            }
            else {
                std::string error((char*)errorBlob->GetBufferPointer());
                THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(DXGI_ERROR_INVALID_CALL, ("[PIXEL SHADER] " + error).c_str());
            }
        }

        if (FAILED(m_Graphics.GetDevice()->CreatePixelShader(m_PsBinary->GetBufferPointer(),
            m_PsBinary->GetBufferSize(), nullptr, &m_PS))) {
            THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(DXGI_ERROR_INVALID_CALL, "Pixel shader creation failed!");;
        }
    }
}