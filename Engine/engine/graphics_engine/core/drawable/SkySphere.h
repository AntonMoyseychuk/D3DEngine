#pragma once
#include "engine/graphics_engine/core/bindable/Texture.h"
#include "Model.h"

namespace graphics_engine::core {
	class SkySphere : public entity::Model
	{
	public:
		SkySphere(const Texture& texture);
	};
}