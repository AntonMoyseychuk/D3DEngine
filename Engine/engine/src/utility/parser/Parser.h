#pragma once
#include <string>

namespace engine::util {
	class Parser
	{
	public:
		static std::wstring ToWString(const std::string& str) { return std::wstring(str.begin(), str.end()); }
		static std::string ToString(const std::wstring& str) { return std::string(str.begin(), str.end()); }
	};
}