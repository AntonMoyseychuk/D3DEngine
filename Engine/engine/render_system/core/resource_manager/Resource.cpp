#include "Resource.h"

namespace engine::graphics::core {
	Resource::Resource(const wchar_t* fullpath)
		: m_Fullpath(fullpath)
	{
	}
	
	const std::wstring& Resource::GetFullpath() const noexcept
	{
		return m_Fullpath;
	}
}