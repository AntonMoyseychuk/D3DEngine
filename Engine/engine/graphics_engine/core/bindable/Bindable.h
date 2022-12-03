#pragma once
#include <stdint.h>
#include "engine/graphics_engine/core/D3DDevice.h"

namespace engine::graphics::core {
	class Bindable
	{
	public:
		virtual void Bind() const noexcept = 0;
		virtual ~Bindable() = default;
	};
}