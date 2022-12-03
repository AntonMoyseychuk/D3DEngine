#pragma once
#include "engine/graphics_engine/core/bindable/ConstantBuffer.h"
#include "engine/graphics_engine/core/drawable/GameObject.h"

namespace graphics_engine::core::entity {
	class Light : protected entity::GameObject<Light> 
	{
	public:
		struct LightConstantBuffer
		{
			DirectX::XMFLOAT3 Position;
			alignas(16) DirectX::XMFLOAT4 Color;
			DirectX::XMFLOAT3 CameraPosition;
		};

	public:
		Light(const DirectX::XMFLOAT3& position = {0.0f, 0.0f, 0.0f}, const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });
		
		void SetPosition(const DirectX::XMFLOAT3& position) noexcept;
		void SetPosition(const DirectX::XMVECTOR& position) noexcept;
		void SetPosition(float x, float y, float z) noexcept;
		void SetPosition(float value) noexcept;
		void AdjustPosition(const DirectX::XMFLOAT3& offset) noexcept;
		void AdjustPosition(const DirectX::XMVECTOR& offset) noexcept;
		void AdjustPosition(float x, float y, float z) noexcept;
		void AdjustPosition(float value) noexcept;
		DirectX::XMFLOAT3 GetPosition() const noexcept;


		void SetColor(const DirectX::XMFLOAT4& color) noexcept;
		void SetColor(const DirectX::XMVECTOR& color) noexcept;
		void SetColor(float r, float g, float b, float a) noexcept;
		void SetColor(float value) noexcept;
		DirectX::XMFLOAT4 GetColor() const noexcept;
		DirectX::XMVECTOR GetColorVector() const noexcept;

		DirectX::XMMATRIX GetTransform() const noexcept override;

		void Update() const;
		void Bind() const;

	private:
		static LightConstantBuffer LightSettings;

	protected:
		DirectX::XMFLOAT4 m_Color;
		core::PSConstantBuffer<LightConstantBuffer> m_LightConstantBuffer;
	};
}