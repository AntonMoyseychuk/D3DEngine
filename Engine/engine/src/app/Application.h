#pragma once
#include "engine/src/graphics/window/Window.h"
#include "engine/src/utility/time/Timer.h"

#include "engine/src/graphics/drawable/SkySphere.h"
#include "engine/src/graphics/drawable/Light.h"

namespace engine::app {
	class Application
	{
	public:
		Application(const wchar_t* title, uint32_t width, uint32_t height);
		int Run();

	private:
		void Update();

	private:
		window::Window m_Window;
		time::Timer m_Timer;

		std::vector<std::unique_ptr<graphics::Drawable>> m_Drawables;
		
		graphics::light::Light m_Light;
		
		graphics::SkySphere m_SkyBox;
	};
}