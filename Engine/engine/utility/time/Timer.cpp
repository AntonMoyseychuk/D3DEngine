#include "Timer.h"

#include "engine/utility/winapi/WinAPI.h"

namespace engine::time {
	Timer::Timer()
	{
		m_Begin = std::chrono::steady_clock::now();
		m_Last = m_Begin;
	}

	float Timer::GetDeltaTime()
	{
		const auto temp = m_Last;
		m_Last = std::chrono::steady_clock::now();
		return std::chrono::duration<float>(m_Last - temp).count();
	}

	float Timer::Peek() const
	{
		return std::chrono::duration<float>(std::chrono::steady_clock::now() - m_Begin).count();
	}
}