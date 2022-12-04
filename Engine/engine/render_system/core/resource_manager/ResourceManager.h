#pragma once
#include <unordered_map>
#include <string>
#include <memory>

#include "Resource.h"


namespace engine::graphics::core {
	class ResourceManager
	{
	public:
		typedef std::shared_ptr<Resource> ResourcePtr;

		ResourceManager() = default;
		virtual ~ResourceManager() = default;

	protected:
		ResourcePtr CreateResourceFromFile(const wchar_t* filepath);
		virtual Resource* CreateResourceFromFileConcrete(const wchar_t* filepath) const = 0;

	private:
		static std::unordered_map<std::wstring, ResourcePtr> m_Resources;
	};
}