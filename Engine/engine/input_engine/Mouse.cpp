#include "Mouse.h"

namespace engine::input {
	Mouse::Event::Event() noexcept
		: m_Type(Type::INVALID), m_Position(std::make_pair(0, 0))
	{
	}

	Mouse::Event::Event(Type type, const Mouse& parent) noexcept
		: m_Type(type), m_Position(parent.m_Position)
	{
	}

	std::pair<float, float> Mouse::Event::GetPosition() const noexcept
	{
		return m_Position;
	}

	Mouse::Event::Type Mouse::Event::GetType() const noexcept
	{
		return m_Type;
	}

	std::pair<float, float> Mouse::GetPosition() const noexcept
	{
		return m_Position;
	}

	Mouse::Event Mouse::ReadEvent() noexcept
	{
		if (!m_EventBuffer.empty()) {
			Event e(m_EventBuffer.front());
			m_EventBuffer.pop();
			return e;
		}

		return Event();
	}

	bool Mouse::IsEventBufferEmpty() const noexcept
	{
		return m_EventBuffer.empty();
	}

	bool Mouse::IsInClientState() const noexcept
	{
		return m_IsInClientState;
	}

	bool Mouse::IsRightButtonPressed() const noexcept
	{
		return m_IsRButtonPressed;
	}

	bool Mouse::IsLeftButtonPressed() const noexcept
	{
		return m_IsLButtonPressed;
	}

	int8_t Mouse::GetScrollDelta() const noexcept
	{
		auto res = m_ScrollDelta;
		m_ScrollDelta = 0;
		return res;
	}

	void Mouse::ClearEventBuffer() noexcept
	{
		m_EventBuffer = std::queue<Event>();
	}

	void Mouse::TrimEventBuffer() noexcept
	{
		while (m_EventBuffer.size() > s_MaxBufferSize) {
			m_EventBuffer.pop();
		}
	}

	void Mouse::OnMove(int32_t x, int32_t y) noexcept
	{
		m_Position.first = x;
		m_Position.second = y;

		m_EventBuffer.push(Event(Event::Type::MOVE, *this));
		TrimEventBuffer();
	}

	void Mouse::OnLeftButtonPressed(int32_t x, int32_t y) noexcept
	{
		m_IsLButtonPressed = true;

		m_Position.first = x;
		m_Position.second = y;

		m_EventBuffer.push(Event(Event::Type::LBUTTON_PRESS, *this));
		TrimEventBuffer();
	}

	void Mouse::OnLeftButtonReleased(int32_t x, int32_t y) noexcept
	{
		m_IsLButtonPressed = false;

		m_Position.first = x;
		m_Position.second = y;

		m_EventBuffer.push(Event(Event::Type::LBUTTON_RELEASE, *this));
		TrimEventBuffer();
	}

	void Mouse::OnRightButtonPressed(int32_t x, int32_t y) noexcept
	{
		m_IsRButtonPressed = true;

		m_Position.first = x;
		m_Position.second = y;

		m_EventBuffer.push(Event(Event::Type::RBUTTON_PRESS, *this));
		TrimEventBuffer();
	}

	void Mouse::OnRightButtonReleased(int32_t x, int32_t y) noexcept
	{
		m_IsRButtonPressed = false;

		m_Position.first = x;
		m_Position.second = y;

		m_EventBuffer.push(Event(Event::Type::RBUTTON_RELEASE, *this));
		TrimEventBuffer();
	}

	void Mouse::OnWheel(int32_t x, int32_t y, int32_t delta) noexcept
	{
		m_Position.first = x;
		m_Position.second = y;

		m_ScrollDelta = delta > 0 ? 1 : delta < 0 ? -1 : 0;

		m_EventBuffer.push(delta > 0 ? Event(Event::Type::WHEEL_UP, *this) : Event(Event::Type::WHEEL_DOWN, *this));
		TrimEventBuffer();
	}

	void Mouse::OnEnter() noexcept
	{
		m_IsInClientState = true;

		m_EventBuffer.push(Event(Event::Type::ENTER, *this));
		TrimEventBuffer();
	}
	void Mouse::OnLeave() noexcept
	{
		m_IsInClientState = false;

		m_EventBuffer.push(Event(Event::Type::LEAVE, *this));
		TrimEventBuffer();
	}
}