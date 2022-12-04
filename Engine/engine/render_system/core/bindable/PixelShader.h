#pragma once
#include "engine/render_system/core/RenderSystem.h"
#include "ConstantBuffer.h"

#include <string>


namespace engine::graphics::core {
	class PixelShader : public Bindable
	{
	public:
		PixelShader(const std::wstring& filepath);

		void Bind() const noexcept override;

	protected:
		void OnCreate();

	private:
		std::wstring m_Filepath = L"";

		Microsoft::WRL::ComPtr<ID3D10Blob> m_PsBinary = nullptr;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS = nullptr;
	};
}