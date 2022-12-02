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

	protected:
		void Render() const noexcept;

		virtual void Update();

	private:
		time::Timer m_Timer;
		window::Window m_Window;

		std::vector<std::unique_ptr<graphics::Drawable>> m_Drawables;
		std::vector<std::unique_ptr<graphics::light::Light>> m_Lights;
		
		graphics::SkySphere m_SkySphere;
	};
}