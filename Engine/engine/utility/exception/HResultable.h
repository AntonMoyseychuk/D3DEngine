#pragma once
#include <string>
#include "engine/utility/winapi/WinAPI.h"
#include "engine/utility/parser/StringParser.h"

namespace graphics_engine::except {
	class HResultable
	{
	public:
		virtual std::string GetErrorString() const noexcept = 0;

	protected:
		virtual std::string TranslateErrorCode(HRESULT result) const noexcept
		{
			wchar_t* msgBuff = nullptr;
			DWORD msgLen = FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				nullptr,
				result,
				MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
				reinterpret_cast<LPWSTR>(&msgBuff),
				0,
				nullptr
			);

			if (msgLen == 0) {
				return "Undefined error code";
			}

			msgBuff[msgLen - 2] = '\0';
			std::string error = util::StringParser::ToString(msgBuff);
			LocalFree(msgBuff);
			return error;
		}
	};
}