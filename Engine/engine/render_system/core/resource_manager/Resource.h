#pragma once
#include <string>

namespace engine::graphics::core {
	class Resource
	{
	public:
		Resource(const std::wstring& fullpath);
		virtual ~Resource() = default;

		const std::wstring& GetSourcePath() const noexcept;

	protected:
		std::wstring m_Fullpath = L"";
	};
}