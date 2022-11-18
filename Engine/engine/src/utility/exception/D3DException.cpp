#include "D3DException.h"
#include "engine/src/utility/parser/Parser.h"

#include <sstream>


namespace engine::except {
#ifndef NDEBUG
	D3DException::D3DException(const char* file, uint32_t line, HRESULT result, std::vector<std::string> info) noexcept
		: Exception(file, line), m_OperationResult(result)
	{
		std::ostringstream oss;
		oss << "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
			<< std::dec << " (" << (uint64_t)GetErrorCode() << ")"
			<< "\n\n[Description] " << GetErrorString();

		if (info.empty()) {
			m_Info = "...";
		}
		else {
			for (const auto& str : info) {
				m_Info += str + '\n';
			}
			oss << "\n\n[Information] " << m_Info;
		}

		m_WhatBuffer = GetType() + ("\n\n" + oss.str() + "\n\n") + m_WhatBuffer;
	}

	D3DException::D3DException(const char* msg, const char* file, uint32_t line, HRESULT result, std::vector<std::string> info) noexcept
		: Exception(msg, file, line), m_OperationResult(result)
	{
		std::ostringstream oss;
		oss << "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
			<< std::dec << " (" << (uint64_t)GetErrorCode() << ")"
			<< "\n\n[Description] " << GetErrorString();

		if (info.empty()) {
			m_Info = "...";
		}
		else {
			for (const auto& str : info) {
				m_Info += str + '\n';
			}
			oss << "\n\n[Information] " << m_Info;
		}

		m_WhatBuffer = GetType() + ("\n\n" + oss.str() + "\n\n") + m_WhatBuffer;
	}

	std::string D3DException::GetInfo() const noexcept
	{
		return m_Info;
	}
#else
	D3DException::D3DException(const char* file, uint32_t line, HRESULT result) noexcept
		: Exception(file, line), m_OperationResult(result)
	{
		std::ostringstream oss;
		oss << "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
			<< std::dec << " (" << (uint64_t)GetErrorCode() << ")"
			<< "\n\n[Description] " << GetErrorString();

		m_WhatBuffer = GetType() + ("\n\n" + oss.str() + "\n\n") + m_WhatBuffer;
	}

	D3DException::D3DException(const char* msg, const char* file, uint32_t line, HRESULT result) noexcept
		: Exception(msg, file, line), m_OperationResult(result)
	{
		std::ostringstream oss;
		oss << "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
			<< std::dec << " (" << (uint64_t)GetErrorCode() << ")"
			<< "\n\n[Description] " << GetErrorString();

		m_WhatBuffer = GetType() + ("\n\n" + oss.str() + "\n\n") + m_WhatBuffer;
	}
#endif

	const char* D3DException::GetType() const noexcept
	{
		return "Graphics Exception";
	}

	std::string D3DException::GetErrorString() const noexcept
	{
		return TranslateErrorCode(m_OperationResult);
	}

	HRESULT D3DException::GetErrorCode() const noexcept
	{
		return m_OperationResult;
	}

	const char* D3DDeviceRemovedException::GetType() const noexcept
	{
		return "Graphics Device Removed Exception";
	}
}