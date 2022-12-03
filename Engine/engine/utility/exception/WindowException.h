#pragma once
#include "HResultable.h"
#include "Exception.h"
#include "engine/utility/winapi/WinAPI.h"

namespace engine::except {
	class WindowException : public Exception, public HResultable
	{
	public:
		WindowException(const char* file, uint32_t line, HRESULT result) noexcept;
		WindowException(const char* msg, const char* file, uint32_t line, HRESULT result) noexcept;

	public:
		HRESULT GetErrorCode() const noexcept;
		const char* GetType() const noexcept override;
		std::string GetErrorString() const noexcept override;

	protected:
		HRESULT m_ResultCode;
	};
}

#define ENGINE_WINDOW_EXCEPTION(hResult) engine::except::WindowException(__FILE__, __LINE__, hResult)
#define ENGINE_WINDOW_EXCEPTION_MSG(hResult, msg) engine::except::WindowException(msg, __FILE__, __LINE__, hResult)
#define ENGINE_WINDOW_LAST_ERROR_EXCEPTION() ENGINE_WINDOW_EXCEPTION(GetLastError())