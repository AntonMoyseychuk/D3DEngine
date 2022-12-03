#pragma once
#include "engine/graphics_engine/core/RenderSystem.h"
#include "ConstantBuffer.h"

#include <string>


namespace graphics_engine::core {
	class PixelShader : public Bindable
	{
	public:
		PixelShader(const std::wstring& filepath);

		void Bind() const noexcept override;

	protected:
		void OnCreate() const;

	private:
		std::wstring m_Filepath = L"";

		mutable Microsoft::WRL::ComPtr<ID3D10Blob> m_PsBinary = nullptr;
		mutable Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS = nullptr;
	};
}