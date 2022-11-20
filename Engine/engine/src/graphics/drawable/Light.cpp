#include "Light.h"

namespace engine::graphics::light {
	Light::LightConstantBuffer Light::LightSettings;

	Light::Light(const Graphics& gfx, const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT4& color)
		: Entity<Light>::Entity(gfx, position, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }), m_Color(color), m_LightConstantBuffer(gfx)
	{
		this->Bind();
	}

	void Light::SetPosition(const DirectX::XMFLOAT3& position) noexcept
	{
		Entity<Light>::SetPosition(position);
	}

	void Light::SetPosition(const DirectX::XMVECTOR& position) noexcept
	{
		Entity<Light>::SetPosition(position);
	}

	void Light::SetPosition(float x, float y, float z) noexcept
	{
		Entity<Light>::SetPosition(x, y, z);
	}

	void Light::SetPosition(float value) noexcept
	{
		Entity<Light>::SetPosition(value, value, value);
	}

	void Light::AdjustPosition(const DirectX::XMFLOAT3& offset) noexcept
	{
		Entity<Light>::AdjustPosition(offset);
	}

	void Light::AdjustPosition(const DirectX::XMVECTOR& offset) noexcept
	{
		Entity<Light>::AdjustPosition(offset);
	}

	void Light::AdjustPosition(float x, float y, float z) noexcept
	{
		Entity<Light>::AdjustPosition(x, y, z);
	}

	void Light::AdjustPosition(float value) noexcept
	{
		Entity<Light>::AdjustPosition(value, value, value);
	}

	DirectX::XMFLOAT3 Light::GetPosition() const noexcept
	{
		return Entity<Light>::GetPosition();
	}

	void Light::SetColor(const DirectX::XMFLOAT4& color) noexcept
	{
		m_Color = color;
	}

	void Light::SetColor(const DirectX::XMVECTOR& color) noexcept
	{
		DirectX::XMStoreFloat4(&m_Color, color);
	}

	void Light::SetColor(float r, float g, float b, float a) noexcept
	{
		m_Color = { r, g, b, a };
	}

	void Light::SetColor(float value) noexcept
	{
		m_Color = { value, value, value, value };
	}

	DirectX::XMFLOAT4 Light::GetColor() const noexcept
	{
		return m_Color;
	}

	DirectX::XMVECTOR Light::GetColorVector() const noexcept
	{
		return DirectX::XMLoadFloat4(&m_Color);
	}

	DirectX::XMMATRIX Light::GetTransform() const noexcept
	{
		return Entity<Light>::GetTransform();
	}

	void Light::Update() const
	{
		LightSettings.Position = this->m_Position;
		LightSettings.Color = this->m_Color;
		m_LightConstantBuffer.Update(LightSettings);
	}

	void Light::Bind() const
	{
		this->Update();
		m_LightConstantBuffer.Bind();
	}
}