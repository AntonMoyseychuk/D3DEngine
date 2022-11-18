#pragma once
#include "Exception.h"
#include "HResultable.h"
#include "engine/src/utility/winapi/WinAPI.h"

#include <vector>

namespace engine::except {
	class D3DException : public Exception, public HResultable
	{
	public:
#ifndef NDEBUG
		D3DException(const char* file, uint32_t line, HRESULT result, std::vector<std::string> info) noexcept;
		D3DException(const char* msg, const char* file, uint32_t line, HRESULT result, std::vector<std::string> info) noexcept;
#else
		D3DException(const char* file, uint32_t line, HRESULT result) noexcept;
		D3DException(const char* msg, const char* file, uint32_t line, HRESULT result) noexcept;
#endif

		HRESULT GetErrorCode() const noexcept;
		const char* GetType() const noexcept override;
		std::string GetErrorString() const noexcept override;
#ifndef NDEBUG
		std::string GetInfo() const noexcept;
#endif

	private:
		HRESULT m_OperationResult;
#ifndef NDEBUG
		std::string m_Info;
#endif
	};

	class D3DDeviceRemovedException : public D3DException
	{
	public:
		using D3DException::D3DException;
		const char* GetType() const noexcept override;
	};
}

#ifndef NDEBUG
#define ENGINE_D3D_EXCEPTION(hResult, info) engine::except::D3DException(__FILE__, __LINE__, hResult, info)
#define ENGINE_D3D_EXCEPTION_MSG(hResult, msg, info) engine::except::D3DException(msg, __FILE__, __LINE__, hResult, info)

#define ENGINE_D3D_DEVICE_REMOVED_EXCEPTION(hResult, info) engine::except::D3DDeviceRemovedException(__FILE__, __LINE__, hResult, info)

#define THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(hResult, msg)\
    throw ENGINE_D3D_EXCEPTION_MSG(hResult, msg, std::vector<std::string>())
#else
#define ENGINE_D3D_EXCEPTION(hResult) engine::except::D3DException(__FILE__, __LINE__, hResult)
#define ENGINE_D3D_EXCEPTION_MSG(hResult, msg) engine::except::D3DException(msg, __FILE__, __LINE__, hResult)

#define ENGINE_D3D_DEVICE_REMOVED_EXCEPTION(hResult) engine::except::D3DDeviceRemovedException(__FILE__, __LINE__, hResult)
#endif