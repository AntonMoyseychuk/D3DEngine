#include "WindowException.h"
#include "engine/src/utility/parser/StringParser.h"

#include <sstream>

namespace engine::except {
	WindowException::WindowException(const char* file, uint32_t line, HRESULT result) noexcept
		: Exception(file, line), m_ResultCode(result)
	{
		std::ostringstream oss;
		oss << GetErrorString() << "\n\n[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
			<< std::dec << " (" << (uint64_t)GetErrorCode() << ")";

		m_WhatBuffer = std::string("[") + GetType() + "]: " + (oss.str() + "\n\n") + m_WhatBuffer;
	}

	WindowException::WindowException(const char* msg, const char* file, uint32_t line, HRESULT result) noexcept
		: Exception(msg, file, line), m_ResultCode(result)
	{
		std::ostringstream oss;
		oss << GetErrorString() << "\n\n[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
			<< std::dec << " (" << (uint64_t)GetErrorCode() << ")";

		m_WhatBuffer = std::string("[") + GetType() + "]: " + (oss.str() + "\n\n") + m_WhatBuffer;
	}

	const char* WindowException::GetType() const noexcept
	{
		return "WINDOW EXCEPTION";
	}

	HRESULT WindowException::GetErrorCode() const noexcept
	{
		return m_ResultCode;
	}

	std::string WindowException::GetErrorString() const noexcept
	{
		return TranslateErrorCode(m_ResultCode);
	}
}