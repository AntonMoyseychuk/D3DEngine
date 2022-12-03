#pragma once
#include <string>
#include <algorithm>

namespace engine::util {
	class StringParser
	{
	public:
		static std::wstring ToWString(const std::string& str) { return std::wstring(str.begin(), str.end()); }
		static std::string ToString(const std::wstring& str) { return std::string(str.begin(), str.end()); }

		static std::string ToUpperCase(const std::string& str) 
		{
			std::string res = str;
			std::transform(str.begin(), str.end(), res.begin(), toupper);

			return res;
		}

		static std::string ToLowerCase(const std::string& str)
		{
			std::string res = str;
			std::transform(str.begin(), str.end(), res.begin(), tolower);

			return res;
		}

		static std::wstring ToUpperCase(const std::wstring& str)
		{
			std::string res = ToString(str);
			res = ToUpperCase(res);

			return ToWString(res);
		}

		static std::wstring ToLowerCase(const std::wstring& str)
		{
			std::string res = ToString(str);
			res = ToLowerCase(res);

			return ToWString(res);
		}
	};
}