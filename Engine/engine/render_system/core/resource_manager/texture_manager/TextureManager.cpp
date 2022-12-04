#include "TextureManager.h"


namespace engine::graphics::core {
	TextureManager& TextureManager::Get()
	{
		static TextureManager manager;
		return manager;
	}


	TextureManager::TextureManager() : ResourceManager()
	{
	}

	TextureManager::TexturePtr TextureManager::CreateTextureFromFile(const wchar_t* filepath) const
	{
		return std::static_pointer_cast<Texture>(TextureManager::TexturePtr((Texture*)CreateResourceFromFileConcrete(filepath)));
	}

	Resource* TextureManager::CreateResourceFromFileConcrete(const wchar_t* filepath) const
	{
		Texture* tex = nullptr;
		try
		{
			tex = new Texture(filepath);
		}
		catch (...) {}

		return tex;
	}
}