#include "SkySphere.h"

namespace graphics_engine::core {
	SkySphere::SkySphere(const Texture& texture)
		: Model("sandbox\\res\\models\\sphere.obj", texture)
	{
		//AddBind(std::make_unique<Texture>(texture), GetBinds().begin());
		SetOwnPixelShader(L"sandbox\\res\\shaders\\SkyBox.hlsl");
	}
}