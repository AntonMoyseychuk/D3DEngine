#pragma once
#include <stdint.h>
#include <bitset>
#include <queue>

namespace engine:: window {
	class Window;
}

namespace engine::input {
	class Keyboard
	{
	public:
		friend class engine::window::Window;

		class Event
		{
		public:
			enum class Type { PRESS, RELEASE };

		public:
			Event() noexcept;
			Event(Type type, uint8_t code) noexcept;

			bool IsPressed() const noexcept;
			uint8_t GetCode() const noexcept;

		private:
			uint8_t m_Code;
			Type m_Type;
		};

	public:
		Keyboard() = default;
		Keyboard(const Keyboard&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;

	public:
		bool IsKeyPressed(uint8_t keyCode) const noexcept;

		Event ReadKey() noexcept;
		char ReadChar() noexcept;

		bool IsKeyBufferEmpty() const noexcept;
		bool IsCharBufferEmpty() const noexcept;

		void ClearState() noexcept;

		void SetAutorepeat(bool state) noexcept;
		bool IsAutorepeatEnable() const noexcept;

	private:
		void OnKeyPressed(uint8_t keyCode) noexcept;
		void OnKeyReleased(uint8_t keyCode) noexcept;
		void OnChar(char ch) noexcept;

		void ClearKeyBuffer() noexcept;
		void ClearCharBuffer() noexcept;
		void ResetStateBuffer() noexcept;

	private:
		template<typename T>
		static void TrimBuffer(std::queue<T>& buffer) noexcept;

	private:
		static constexpr uint32_t s_KeyCount = 256u;
		static constexpr uint32_t s_MaxBufferSize = 16u;

	private:
		bool m_IsAutorepeatEnable = false;

		std::bitset<s_KeyCount> m_KeyStates;
		std::queue<Event> m_KeyBuffer;
		std::queue<char> m_CharBuffer;
	};
}

