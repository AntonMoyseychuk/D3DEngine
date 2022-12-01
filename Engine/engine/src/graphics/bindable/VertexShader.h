#pragma once
#include "engine/src/graphics/Graphics.h"
#include "ConstantBuffer.h"

#include <string>
#include <vector>
#include <memory>


namespace engine::graphics {
	class VertexShader : public Bindable
	{
	public:
		enum class InputLayoutAttribute : uint32_t { POSITION = 0u, COLOR, NORMAL, TEXTURE };

	public:
		VertexShader(const std::wstring& filepath);
		VertexShader(const std::wstring& filepath, const std::vector<InputLayoutAttribute>& attribs);

		void SetInputLayout(const std::vector<InputLayoutAttribute>& attribs);

		void Bind() const noexcept override;

	protected:
		void OnSetInputLayout() const;
		void OnCreate() const;

	private:
		std::wstring m_Filepath = L"";

		mutable Microsoft::WRL::ComPtr<ID3D10Blob> m_VsBinary = nullptr;
		mutable Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VS = nullptr;

		mutable Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout = nullptr;
		std::vector<D3D11_INPUT_ELEMENT_DESC> m_InputLayoutDesc = {};
	};
}