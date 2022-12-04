#pragma once
#include <string>
#include <d3dx11.h>
#include <wrl.h>

#include "engine/render_system/core/bindable/Bindable.h"
#include "engine/render_system/core/resource_manager/Resource.h"

namespace engine::graphics::core {
	class TextureManager;

	class Texture : public Resource, public Bindable
	{
		friend class TextureManager;
	public:
		void Bind() const noexcept override;

	private:
		Texture(const wchar_t* filepath);
		void OnCreate() const;

	private:
		mutable Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ID = nullptr;
		mutable Microsoft::WRL::ComPtr<ID3D11SamplerState> m_SamplerState = nullptr;
	};
}