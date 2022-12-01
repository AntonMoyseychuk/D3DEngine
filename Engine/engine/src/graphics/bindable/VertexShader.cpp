#include "VertexShader.h"

#include <d3dcompiler.h>
#include <stdarg.h>

namespace engine::graphics {
    VertexShader::VertexShader(const std::wstring& filepath)
        : Bindable(), m_Filepath(filepath)
    {
        OnCreate();
    }

    VertexShader::VertexShader(const std::wstring& filepath, const std::vector<InputLayoutAttribute>& attribs)
        : Bindable(), m_Filepath(filepath)
    {
        OnCreate();

        SetInputLayout(attribs);
    }

    void VertexShader::SetInputLayout(const std::vector<InputLayoutAttribute>& attribs)
    {
        THROW_EXCEPTION_IF_LOGIC_ERROR(attribs.empty(), "VERTEX SHADER", "The size of \"attribs\" must be greater than 0!");

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
                THROW_EXCEPTION_IF_LOGIC_ERROR(true, "VERTEX SHADER", "Invalid attribute value [Attribute = "
                    + std::to_string(static_cast<uint32_t>(attrib)) + "]");
                break;
            }
        }

        OnSetInputLayout();
    }

    void VertexShader::Bind() const noexcept
    {
        D3DDevice::Get().GetDeviceContextD3D11()->VSSetShader(m_VS.Get(), nullptr, 0);
    }

    void VertexShader::OnSetInputLayout() const
    {
        Bind();

        THROW_EXCEPTION_IF_LOGIC_ERROR(m_InputLayoutDesc.empty(), "VERTEX SHADER", "Input Layout in not set!");

        HRESULT hr = D3DDevice::Get().GetDeviceD3D11()->CreateInputLayout(m_InputLayoutDesc.data(), m_InputLayoutDesc.size(),
            m_VsBinary->GetBufferPointer(), m_VsBinary->GetBufferSize(), &m_InputLayout);
        THROW_EXCEPTION_IF_HRESULT_ERROR(hr, "VERTEX SHADER", "Input Layout creation failed!\nCheck the correctness of the arguments.");
        D3DDevice::Get().GetDeviceContextD3D11()->IASetInputLayout(m_InputLayout.Get());
    }

    void VertexShader::OnCreate() const
    {
        Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
        if (FAILED(D3DX11CompileFromFile(m_Filepath.c_str(), nullptr, nullptr,
            "main", "vs_4_0", 0, 0, nullptr, &m_VsBinary, &errorBlob, nullptr)))
        {
            if (errorBlob == nullptr) {
                THROW_EXCEPTION_IF_LOGIC_ERROR(true, "VERTEX SHADER", 
                    "Invalid vertex shader filepath: " + util::StringParser::ToString(m_Filepath));
            }
            else {
                std::string error((char*)errorBlob->GetBufferPointer());
                THROW_EXCEPTION_IF_LOGIC_ERROR(true, "VERTEX SHADER", error);
            }
        }

        HRESULT hr = D3DDevice::Get().GetDeviceD3D11()->CreateVertexShader(m_VsBinary->GetBufferPointer(),
            m_VsBinary->GetBufferSize(), nullptr, &m_VS);
        THROW_EXCEPTION_IF_HRESULT_ERROR(hr, "VERTEX SHADER", "Vertex shader creation failed!");
    }
}