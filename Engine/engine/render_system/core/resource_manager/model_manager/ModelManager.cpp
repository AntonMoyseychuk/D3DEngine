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

	ModelPtr ModelManager::CreateModelFromFile(const wchar_t* filepath) const
	{
		return std::static_pointer_cast<Model>(ModelPtr(
			dynamic_cast<Model*>(CreateResourceFromFileConcrete(filepath))
		));
	}

	Resource* ModelManager::CreateResourceFromFileConcrete(const wchar_t* filepath) const
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