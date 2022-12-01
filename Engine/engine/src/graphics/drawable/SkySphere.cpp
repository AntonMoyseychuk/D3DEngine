#include "SkySphere.h"

namespace engine::graphics {
	SkySphere::SkySphere(const Texture& texture)
		: Model("sandbox\\res\\models\\sphere.obj")
	{
		AddBind(std::make_unique<Texture>(texture), GetBinds().begin());
		SetOwnPixelShader(L"sandbox\\res\\shaders\\SkyBox.hlsl");
	}
}