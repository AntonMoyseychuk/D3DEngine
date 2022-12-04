#include "Resource.h"

namespace engine::graphics::core {
	Resource::Resource(const std::wstring& fullpath)
		: m_Fullpath(fullpath)
	{
	}
	
	const std::wstring& Resource::GetSourcePath() const noexcept
	{
		return m_Fullpath;
	}
}