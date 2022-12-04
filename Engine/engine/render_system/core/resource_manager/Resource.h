#pragma once
#include <string>

namespace engine::graphics::core {
	class Resource
	{
	public:
		Resource(const wchar_t* fullpath);
		virtual ~Resource() = default;

		const std::wstring& GetFullpath() const noexcept;

	protected:
		std::wstring m_Fullpath = L"";
	};
}