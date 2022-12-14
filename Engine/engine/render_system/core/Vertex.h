#pragma once
#include <DirectXMath.h>

namespace engine::graphics::core {
	struct Vertex
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT2 Texture;
		DirectX::XMFLOAT3 Normal;
	};
}