#pragma once
#include <queue>

namespace engine {
	namespace window {
		class Window;
	}
}

namespace engine {
	namespace input {
		class Mouse
		{
		public:
			friend class engine::window::Window;

			class Event
			{
			public:
				enum class Type 
				{
					LBUTTON_PRESS,
					LBUTTON_RELEASE,
					RBUTTON_PRESS,
					RBUTTON_RELEASE,
					WHEEL_UP,
					WHEEL_DOWN,
					MOVE,
					ENTER,
					LEAVE,
					INVALID
				};

			public:
				Event() noexcept;
				Event(Type type, const Mouse& parent) noexcept;

				std::pair<float, float> GetPosition() const noexcept;
				Type GetType() const noexcept;

			private:
				Type m_Type;
				std::pair<float, float> m_Position;
			};

		public:
			Mouse() = default;

			Mouse(const Mouse&) = delete;
			Mouse& operator=(const Mouse&) = delete;

			std::pair<float, float> GetPosition() const noexcept;

			Event ReadEvent() noexcept;
			bool IsEventBufferEmpty() const noexcept;
			bool IsInClientState() const noexcept;
			bool IsRightButtonPressed() const noexcept;
			bool IsLeftButtonPressed() const noexcept;
			int8_t GetScrollDelta() const noexcept;

		private:
			void ClearEventBuffer() noexcept;
			void TrimEventBuffer() noexcept;

			void OnMove(int32_t x, int32_t y) noexcept;
			void OnLeftButtonPressed(int32_t x, int32_t y) noexcept;
			void OnLeftButtonReleased(int32_t x, int32_t y) noexcept;
			void OnRightButtonPressed(int32_t x, int32_t y) noexcept;
			void OnRightButtonReleased(int32_t x, int32_t y) noexcept;
			void OnWheel(int32_t x, int32_t y, int32_t delta) noexcept;
			void OnEnter() noexcept;
			void OnLeave() noexcept;

		private:
			static constexpr uint32_t s_MaxBufferSize = 16u;

		private:
			std::pair<float, float> m_Position;
			std::queue<Event> m_EventBuffer;
			bool m_IsInClientState;

			mutable int8_t m_ScrollDelta = 0;

			bool m_IsLButtonPressed = false;
			bool m_IsRButtonPressed = false;
		};
	}
}