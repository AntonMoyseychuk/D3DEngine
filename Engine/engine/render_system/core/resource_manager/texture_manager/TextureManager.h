#pragma once
#include "../ResourceManager.h"
#include "engine/render_system/core/resource_manager/texture_manager/Texture.h"

namespace engine::graphics::core {
	class TextureManager : public ResourceManager
	{
	public:
		typedef std::shared_ptr<Texture> TexturePtr;

		static TextureManager& Get();
		TexturePtr CreateTextureFromFile(const wchar_t* filepath) const;

	protected:
		TextureManager();

		Resource* CreateResourceFromFileConcrete(const wchar_t* filepath) const override;
	};
}