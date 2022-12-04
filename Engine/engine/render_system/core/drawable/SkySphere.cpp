#include "SkySphere.h"

namespace engine::graphics::core {
	SkySphere::SkySphere(const Texture& texture)
		: Model("sandbox\\res\\models\\sphere.obj", texture)
	{
		//AddBind(std::make_unique<Texture>(texture), GetBinds().begin());
		SetOwnPixelShader(L"sandbox\\res\\shaders\\SkyBox.hlsl");
	}
}