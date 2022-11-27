#include "SkySphere.h"

namespace engine::graphics {
	SkySphere::SkySphere(const Graphics& gfx, const Texture& texture)
		: Model(gfx, "sandbox\\res\\models\\sphere.obj")
	{
		AddBind(std::make_unique<Texture>(texture), GetBinds().begin());
		SetOwnPixelShader(L"sandbox\\res\\shaders\\SkyBox.hlsl");
	}
}