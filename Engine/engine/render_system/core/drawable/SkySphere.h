#pragma once
#include "engine/render_system/core/resource_manager/texture_manager/Texture.h"
#include "Model.h"

namespace engine::graphics::core {
	class SkySphere : public entity::Model
	{
	public:
		SkySphere(const Texture& texture);
	};
}