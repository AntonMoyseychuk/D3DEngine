#pragma once
#include "engine/src/graphics/D3DDevice.h"

namespace engine::graphics {
	class Bindable
	{
	public:
		virtual void Bind() const noexcept = 0;
		virtual ~Bindable() = default;
	};
}