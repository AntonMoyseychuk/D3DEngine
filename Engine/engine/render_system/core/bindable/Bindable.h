#pragma once
#include <stdint.h>
#include "engine/render_system/core/D3DDevice.h"

namespace engine::graphics::core {
	class Bindable
	{
	public:
		Bindable() = default;
		virtual ~Bindable() = default;
		
		virtual void Bind() const noexcept = 0;
	};
}