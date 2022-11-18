#include "Keyboard.h"

namespace engine::input {
	Keyboard::Event::Event() noexcept
		: m_Type(Type::RELEASE), m_Code(0u)
	{
	}

	Keyboard::Event::Event(Type type, uint8_t code) noexcept
		: m_Type(type), m_Code(code)
	{
	}

	bool Keyboard::Event::IsPressed() const noexcept
	{
		return m_Type == Type::PRESS;
	}

	uint8_t Keyboard::Event::GetCode() const noexcept
	{
		return m_Code;
	}


	bool Keyboard::IsKeyPressed(uint8_t keyCode) const noexcept
	{
		return m_KeyStates[keyCode];
	}

	Keyboard::Event Keyboard::ReadKey() noexcept
	{
		if (!m_KeyBuffer.empty()) {
			Event e(m_KeyBuffer.front());
			m_KeyBuffer.pop();
			return e;
		}
		return Event();
	}

	char Keyboard::ReadChar() noexcept
	{
		if (!m_CharBuffer.empty()) {
			char ch = m_CharBuffer.front();
			m_CharBuffer.pop();
			return ch;
		}
		return 0;
	}

	bool Keyboard::IsKeyBufferEmpty() const noexcept
	{
		return m_KeyBuffer.empty();
	}

	void Keyboard::ClearKeyBuffer() noexcept
	{
		m_KeyBuffer = std::queue<Event>();
	}

	bool Keyboard::IsCharBufferEmpty() const noexcept
	{
		return m_CharBuffer.empty();
	}

	void Keyboard::ClearCharBuffer() noexcept
	{
		m_CharBuffer = std::queue<char>();
	}

	void Keyboard::ClearState() noexcept
	{
		ClearCharBuffer();
		ClearKeyBuffer();
		ResetStateBuffer();
	}

	void Keyboard::SetAutorepeat(bool state) noexcept
	{
		m_IsAutorepeatEnable = state;
	}

	bool Keyboard::IsAutorepeatEnable() const noexcept
	{
		return m_IsAutorepeatEnable;
	}

	void Keyboard::OnKeyPressed(uint8_t keyCode) noexcept
	{
		m_KeyStates[keyCode] = true;
		m_KeyBuffer.push(Event(Event::Type::PRESS, keyCode));
		TrimBuffer(m_KeyBuffer);
	}

	void Keyboard::OnKeyReleased(uint8_t keyCode) noexcept
	{
		m_KeyStates[keyCode] = false;
		m_KeyBuffer.push(Event(Event::Type::RELEASE, keyCode));
		TrimBuffer(m_KeyBuffer);
	}

	void Keyboard::OnChar(char ch) noexcept
	{
		m_CharBuffer.push(ch);
		TrimBuffer(m_CharBuffer);
	}

	void Keyboard::ResetStateBuffer() noexcept
	{
		m_KeyStates.reset();
	}

	template<typename T>
	void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
	{
		while (buffer.size() > s_MaxBufferSize) {
			buffer.pop();
		}
	}
}