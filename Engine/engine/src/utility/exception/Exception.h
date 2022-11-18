#pragma once
#include <string>
#include <exception>

namespace engine::except {
	class Exception : public std::exception
	{
	public:
		Exception(const char* file, uint32_t line) noexcept;
		Exception(const char* msg, const char* file, uint32_t line) noexcept;

		const char* what() const noexcept override;

		virtual const char* GetType() const noexcept;
		const char* GetFile() const noexcept;
		std::string GetLocationString() const noexcept;
		uint32_t GetLine() const noexcept;

	protected:
		mutable std::string m_WhatBuffer;

	private:
		uint32_t m_Line;
		std::string m_File;
	};
}

#define ENGINE_EXCEPTION() engine::except::Exception(__FILE__, __LINE__)
#define ENGINE_EXCEPTION_MSG(msg) engine::except::Exception(msg, __FILE__, __LINE__)