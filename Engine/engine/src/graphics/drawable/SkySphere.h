#pragma once
#include "engine/src/graphics/bindable/Texture.h"
#include "Model.h"

namespace engine::graphics {
	class SkySphere : public entity::Model
	{
	public:
		SkySphere(const Graphics& gfx, const Texture& texture);
	};
}