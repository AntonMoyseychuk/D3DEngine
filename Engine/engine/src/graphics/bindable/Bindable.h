#pragma once
#include "engine/src/graphics/Graphics.h"

namespace engine::graphics {
	class Bindable
	{
	public:
		Bindable(const Graphics& gfx) : m_Graphics(gfx) {}

		const Graphics& GetGraphics() const noexcept { return m_Graphics; }

		virtual void Bind() const noexcept = 0;
		virtual ~Bindable() = default;

	protected:
		const Graphics& m_Graphics;
	};
}