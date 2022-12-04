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

	TexturePtr TextureManager::CreateTextureFromFile(const std::wstring& filepath)
	{
		return std::static_pointer_cast<Texture>(CreateResourceFromFile(filepath));
	}

	Resource* TextureManager::CreateResourceFromFileConcrete(const std::wstring& filepath)
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