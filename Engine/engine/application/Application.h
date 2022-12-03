#pragma once
#include "engine/window/Window.h"
#include "engine/utility/time/Timer.h"

#include "engine/graphics_engine/core/drawable/Drawable.h"

#include "engine/graphics_engine/core/drawable/SkySphere.h"
#include "engine/graphics_engine/core/drawable/Light.h"

namespace engine::app {
	class Application
	{
	public:
		Application(const wchar_t* title, uint32_t width, uint32_t height);
		int Run();

	protected:
		void Render() const noexcept;

		virtual void Update();

	private:
		
		time::Timer m_Timer;
		window::Window m_Window;

		std::vector<std::unique_ptr<graphics::core::Drawable>> m_Drawables;
		std::vector<std::unique_ptr<graphics::core::entity::Light>> m_Lights;
		
		graphics::core::SkySphere m_SkySphere;
	};
}