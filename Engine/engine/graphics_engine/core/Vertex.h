#pragma once
#include <DirectXMath.h>

namespace graphics_engine::core {
	struct Vertex
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT2 Texture;
		DirectX::XMFLOAT3 Normal;
	};
}