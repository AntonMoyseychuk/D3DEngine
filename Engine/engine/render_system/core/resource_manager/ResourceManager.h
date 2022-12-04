#pragma once
#include <unordered_map>
#include <string>
#include <memory>

#include "Resource.h"


namespace engine::graphics::core {
	typedef std::shared_ptr<Resource> ResourcePtr;
	
	class ResourceManager
	{
	public:
		ResourceManager() = default;
		virtual ~ResourceManager() = default;

	protected:
		ResourcePtr CreateResourceFromFile(const std::wstring& filepath);
		virtual Resource* CreateResourceFromFileConcrete(const std::wstring& filepath) = 0;

	private:
		static std::unordered_map<std::wstring, ResourcePtr> m_Resources;
	};
}