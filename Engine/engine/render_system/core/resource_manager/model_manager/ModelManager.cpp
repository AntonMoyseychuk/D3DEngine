#include "ModelManager.h"

namespace engine::graphics::core {
	ModelManager& ModelManager::Get()
	{
		static ModelManager manager;
		return manager;
	}

	ModelManager::ModelManager() : ResourceManager()
	{
	}

	ModelPtr ModelManager::CreateModelFromFile(const std::wstring& filepath)
	{
		return std::static_pointer_cast<Model>(CreateResourceFromFile(filepath));
	}

	Resource* ModelManager::CreateResourceFromFileConcrete(const std::wstring& filepath)
	{
		Model* model = nullptr;
		try
		{
			model = new Model(filepath);
		}
		catch (...) {}

		return model;
	}
}