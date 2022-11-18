#pragma once
#include "engine/src/graphics/Graphics.h"
#include "ConstantBuffer.h"

#include <string>


namespace engine::graphics {
	class PixelShader : public Bindable
	{
	public:
		PixelShader(const Graphics& gfx, const wchar_t* filepath);

		void Bind() const noexcept override;

	protected:
		void OnCreate() const;

	private:
		std::wstring m_Filepath = L"";

		mutable Microsoft::WRL::ComPtr<ID3D10Blob> m_PsBinary = nullptr;
		mutable Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS = nullptr;
	};
}