#include "VertexShader.h"
#include "engine/src/utility/exception/D3DException.h"

#include <d3dcompiler.h>
#include <stdarg.h>

namespace engine::graphics {
    VertexShader::VertexShader(const Graphics& gfx, const wchar_t* filepath)
        : Bindable(gfx), m_Filepath(filepath)
    {
        OnCreate();
    }

    VertexShader::VertexShader(const Graphics& gfx, const wchar_t* filepath, const std::vector<InputLayoutAttribute>& attribs)
        : Bindable(gfx), m_Filepath(filepath)
    {
        OnCreate();

        SetInputLayout(attribs);
    }

    void VertexShader::SetInputLayout(const std::vector<InputLayoutAttribute>& attribs)
    {
        if (attribs.empty()) {
            THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(E_INVALIDARG,
                "The size of \"attribs\" must be greater than 0!");
        }

        for (const auto& attrib : attribs) {
            switch (attrib)
            {
            case InputLayoutAttribute::POSITION:
                m_InputLayoutDesc.push_back(
                    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
                );
                break;

            case InputLayoutAttribute::COLOR:
                m_InputLayoutDesc.push_back(
                    { "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
                );
                break;

            case InputLayoutAttribute::TEXTURE:
                m_InputLayoutDesc.push_back(
                    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
                );
                break;

            case InputLayoutAttribute::NORMAL:
                m_InputLayoutDesc.push_back(
                    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
                );
                break;

            default:
                THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(E_INVALIDARG, ("Invalid attribute value [Attribute = "
                    + std::to_string(static_cast<uint32_t>(attrib)) + "]").c_str()
                );
                break;
            }
        }

        OnSetInputLayout();
    }

    void VertexShader::Bind() const noexcept
    {
        m_Graphics.GetDeviceContext()->VSSetShader(m_VS.Get(), nullptr, 0);
    }

    void VertexShader::OnSetInputLayout() const
    {
        Bind();

        if (m_InputLayoutDesc.empty()) {
            THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(E_INVALIDARG, "Input Layout in not set!");
        }

        if (FAILED(m_Graphics.GetDevice()->CreateInputLayout(m_InputLayoutDesc.data(), m_InputLayoutDesc.size(),
            m_VsBinary->GetBufferPointer(), m_VsBinary->GetBufferSize(), &m_InputLayout))) {
            THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(DXGI_ERROR_INVALID_CALL,
                "Input Layout creation failed!\nCheck the correctness of the arguments.");
        }
        m_Graphics.GetDeviceContext()->IASetInputLayout(m_InputLayout.Get());
    }

    void VertexShader::OnCreate() const
    {
        Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
        if (FAILED(D3DX11CompileFromFile(m_Filepath.c_str(), nullptr, nullptr,
            "main", "vs_4_0", 0, 0, nullptr, &m_VsBinary, &errorBlob, nullptr)))
        {
            if (errorBlob == nullptr) {
                THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(D3D11_ERROR_FILE_NOT_FOUND,
                    ("Invalid vertex shader filepath: " + util::Parser::ToString(m_Filepath)).c_str());
            }
            else {
                std::string error((char*)errorBlob->GetBufferPointer());
                THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(DXGI_ERROR_INVALID_CALL, ("[VERTEX SHADER] " + error).c_str());
            }
        }

        if (FAILED(m_Graphics.GetDevice()->CreateVertexShader(m_VsBinary->GetBufferPointer(),
            m_VsBinary->GetBufferSize(), nullptr, &m_VS))) {
            THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(DXGI_ERROR_INVALID_CALL, "Vertex shader creation failed!");
        }
    }
}