#pragma once
#include <chrono>

namespace graphics_engine::time {
	class Timer
	{
	public:
		Timer();
		float GetDeltaTime();
		float Peek() const;

	private:
		std::chrono::steady_clock::time_point m_Last;
		std::chrono::steady_clock::time_point m_Begin;
	};
}