#pragma once
#include "engine/render_system/core/bindable/Texture.h"
#include "Model.h"

namespace engine::graphics::core {
	class SkySphere : public entity::Model
	{
	public:
		SkySphere(const Texture& texture);
	};
}