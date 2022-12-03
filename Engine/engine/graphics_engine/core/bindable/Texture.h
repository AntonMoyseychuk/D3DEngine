#pragma once
#include <string>
#include <d3dx11.h>
#include <wrl.h>

#include "Bindable.h"

namespace graphics_engine::core {
	class Texture : public Bindable
	{
	public:
		Texture(const wchar_t* filepath);
		void Bind() const noexcept override;

	private:
		void OnCreate() const;

	private:
		std::wstring m_Filepath = L"";

		mutable Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ID = nullptr;
		mutable Microsoft::WRL::ComPtr<ID3D11SamplerState> m_SamplerState = nullptr;
	};
}