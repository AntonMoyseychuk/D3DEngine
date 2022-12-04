#include "ResourceManager.h"

#if __cplusplus <= 201402L 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

#if __cplusplus >= 201703L
#include <filesystem>
#endif

namespace engine::graphics::core {
	std::unordered_map<std::wstring, ResourceManager::ResourcePtr> ResourceManager::m_Resources;

	ResourceManager::ResourcePtr ResourceManager::CreateResourceFromFile(const wchar_t* filepath)
	{
		#if (_MSC_VER >= 1900 && _MSC_VER <= 1916)  || ( _MSC_VER >= 1920 && __cplusplus <= 201402L) 
				std::wstring fullpath = std::experimental::filesystem::absolute(filepath);
		#endif
		
		#if _MSC_VER >= 1920 && __cplusplus > 201402L 
				std::wstring fullpath = std::filesystem::absolute(filepath);
		#endif

		auto it = m_Resources.find(fullpath);
		if (it != m_Resources.end()) {
			return it->second;
		}

		auto resource = std::make_shared<Resource>(*this->CreateResourceFromFileConcrete(fullpath.c_str()));

		if (resource != nullptr) {
			m_Resources[fullpath] = resource;
		}

		return resource;
	}
}