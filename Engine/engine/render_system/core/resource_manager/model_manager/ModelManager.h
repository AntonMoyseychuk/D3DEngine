#pragma once
#include "../ResourceManager.h"
#include "engine/render_system/core/drawable/Model.h"

namespace engine::graphics::core {
	typedef std::shared_ptr<Model> ModelPtr;

	class ModelManager : public ResourceManager
	{
	public:
		static ModelManager& Get();
		ModelPtr CreateModelFromFile(const wchar_t* filepath) const;

	protected:
		ModelManager();

		Resource* CreateResourceFromFileConcrete(const wchar_t* filepath) const override;
	};
}