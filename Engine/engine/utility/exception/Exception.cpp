#include "Exception.h"

namespace graphics_engine::except {
	Exception::Exception(const char* msg, const char* file, uint32_t line) noexcept
		: m_File(file), m_Line(line)
	{
		m_WhatBuffer = "[Message] " + std::string(msg) + "\n\n" + GetLocationString();
	}

	Exception::Exception(const char* file, uint32_t line) noexcept
		: m_File(file), m_Line(line)
	{
		m_WhatBuffer = GetLocationString();
	}

	const char* Exception::what() const noexcept
	{
		return m_WhatBuffer.c_str();
	}

	const char* Exception::GetType() const noexcept
	{
		return "BASE ENGINE EXCEPTION";
	}

	const char* Exception::GetFile() const noexcept
	{
		return m_File.c_str();
	}

	std::string Exception::GetLocationString() const noexcept
	{
		return "[File]" + m_File + " (line: " + std::to_string(m_Line) + ")";
	}

	uint32_t Exception::GetLine() const noexcept
	{
		return m_Line;
	}
}