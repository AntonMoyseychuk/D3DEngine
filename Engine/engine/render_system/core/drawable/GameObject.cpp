#include "GameObject.h"

namespace engine::graphics::core {
	GameObject::GameObject(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& scale, const DirectX::XMFLOAT3& rotation)
		: m_Position(position), m_Scale(scale), m_RotationAngle(rotation)
	{
	}

	void GameObject::SetPosition(const DirectX::XMFLOAT3& position) noexcept
	{
		m_Position = position;
	}
	void GameObject::SetPosition(const DirectX::XMVECTOR& position) noexcept
	{
		DirectX::XMStoreFloat3(&m_Position, position);
	}
	void GameObject::SetPosition(float x, float y, float z) noexcept
	{
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
	}
	void GameObject::SetPosition(float value) noexcept
	{
		m_Position.x = value;
		m_Position.y = value;
		m_Position.z = value;
	}
	void GameObject::AdjustPosition(const DirectX::XMFLOAT3& offset) noexcept
	{
		m_Position.x += offset.x;
		m_Position.y += offset.y;
		m_Position.z += offset.z;
	}
	void GameObject::AdjustPosition(const DirectX::XMVECTOR& offset) noexcept
	{
		using namespace DirectX;
		auto pos = XMLoadFloat3(&m_Position) + offset;
		XMStoreFloat3(&m_Position, pos);
	}
	void GameObject::AdjustPosition(float x, float y, float z) noexcept
	{
		m_Position.x += x;
		m_Position.y += y;
		m_Position.z += z;
	}
	void GameObject::AdjustPosition(float value) noexcept
	{
		m_Position.x += value;
		m_Position.y += value;
		m_Position.z += value;
	}
	DirectX::XMFLOAT3 GameObject::GetPosition() const noexcept
	{
		return m_Position;
	}
	DirectX::XMVECTOR GameObject::GetPositionVector() const noexcept
	{
		return DirectX::XMLoadFloat3(&m_Position);
	}


	void GameObject::SetRotation(const DirectX::XMFLOAT3& rotation) noexcept
	{
		m_RotationAngle = rotation;
	}
	void GameObject::SetRotation(const DirectX::XMVECTOR& rotation) noexcept
	{
		DirectX::XMStoreFloat3(&m_RotationAngle, rotation);
	}
	void GameObject::SetRotation(float x, float y, float z) noexcept
	{
		m_RotationAngle.x = x;
		m_RotationAngle.y = y;
		m_RotationAngle.z = z;
	}
	void GameObject::SetRotation(float value) noexcept
	{
		m_RotationAngle.x = value;
		m_RotationAngle.y = value;
		m_RotationAngle.z = value;
	}
	void GameObject::AdjustRotation(const DirectX::XMFLOAT3& angle) noexcept
	{
		m_RotationAngle.x += angle.x;
		m_RotationAngle.y += angle.y;
		m_RotationAngle.z += angle.z;
	}
	void GameObject::AdjustRotation(const DirectX::XMVECTOR& angle) noexcept
	{
		using namespace DirectX;
		auto rotation = XMLoadFloat3(&m_RotationAngle) + angle;
		XMStoreFloat3(&m_RotationAngle, rotation);
	}
	void GameObject::AdjustRotation(float x, float y, float z) noexcept
	{
		m_RotationAngle.x += x;
		m_RotationAngle.y += y;
		m_RotationAngle.z += z;
	}
	void GameObject::AdjustRotation(float value) noexcept
	{
		m_RotationAngle.x += value;
		m_RotationAngle.y += value;
		m_RotationAngle.z += value;
	}
	DirectX::XMFLOAT3 GameObject::GetRotation() const noexcept
	{
		return m_RotationAngle;
	}
	DirectX::XMVECTOR GameObject::GetRotationVector() const noexcept
	{
		return DirectX::XMLoadFloat3(&m_RotationAngle);
	}


	void GameObject::Scale(const DirectX::XMFLOAT3& scale) noexcept
	{
		m_Scale = scale;
	}
	void GameObject::Scale(float x, float y, float z) noexcept
	{
		m_Scale.x = x;
		m_Scale.y = y;
		m_Scale.z = z;
	}
	void GameObject::Scale(float value) noexcept
	{
		m_Scale.x = value;
		m_Scale.y = value;
		m_Scale.z = value;
	}
	DirectX::XMFLOAT3 GameObject::GetScale() const noexcept
	{
		return m_Scale;
	}
	DirectX::XMVECTOR GameObject::GetScaleVector() const noexcept
	{
		return DirectX::XMLoadFloat3(&m_Scale);
	}


	DirectX::XMMATRIX GameObject::GetTransform() const noexcept
	{
		return DirectX::XMMatrixIdentity()
			* DirectX::XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z)
			* DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_RotationAngle.x))
			* DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_RotationAngle.y))
			* DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_RotationAngle.z))
			* DirectX::XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	}
}