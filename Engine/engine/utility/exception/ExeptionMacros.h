#pragma once
#include "engine/utility/parser/StringParser.h"

#define THROW_EXCEPTION_IF_LOGIC_ERROR(condition, exceptionType, msg)\
if ((condition))\
	throw std::exception(("[" + engine::util::StringParser::ToUpperCase(exceptionType) + " EXCEPTION]: " + msg + "\n\n[File]" + __FILE__ +  " (line: " + std::to_string(__LINE__) + ")").c_str())

#define THROW_EXCEPTION_IF_HRESULT_ERROR(hResult, exceptionType, msg) THROW_EXCEPTION_IF_LOGIC_ERROR(FAILED(hResult), exceptionType, msg)