#pragma once
#include <stdint.h>
#include "engine/graphics_engine/core/D3DDevice.h"

namespace graphics_engine::core {
	class Bindable
	{
	public:
		virtual void Bind() const noexcept = 0;
		virtual ~Bindable() = default;
	};
}