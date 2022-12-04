#pragma once
#include "../ResourceManager.h"
#include "engine/render_system/core/bindable/Texture.h"

namespace engine::graphics::core {
	typedef std::shared_ptr<Texture> TexturePtr;
	
	class TextureManager : public ResourceManager
	{
	public:
		static TextureManager& Get();
		TexturePtr CreateTextureFromFile(const std::wstring& filepath);

	protected:
		TextureManager();

		Resource* CreateResourceFromFileConcrete(const std::wstring& filepath) override;
	};
}