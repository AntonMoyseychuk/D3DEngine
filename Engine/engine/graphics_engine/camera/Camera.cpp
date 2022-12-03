#include "Camera.h"

#include "engine/utility/winapi/WinAPI.h"

namespace graphics_engine::core {
    const DirectX::XMVECTOR Camera::DEFAULT_BACKWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
    const DirectX::XMVECTOR Camera::DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    const DirectX::XMVECTOR Camera::DEFAULT_RIGHT_VECTOR = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
    const DirectX::XMVECTOR Camera::DEFAULT_LEFT_VECTOR = DirectX::XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
    const DirectX::XMVECTOR Camera::DEFAULT_DOWN_VECTOR = DirectX::XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f);
    const DirectX::XMVECTOR Camera::DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    Camera::Camera(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& rotation)
        : m_Position(position), m_Rotation(rotation)
    {
        this->Update();
    }

    DirectX::XMFLOAT3 Camera::GetPosition() const noexcept
    {
        return m_Position;
    }

    DirectX::XMVECTOR Camera::GetPositionVector() const noexcept
    {
        return DirectX::XMLoadFloat3(&m_Position);
    }

    void Camera::SetPosition(const DirectX::XMFLOAT3& position) noexcept
    {
        m_Position = position;
        this->Update();
    }

    void Camera::SetPosition(float x, float y, float z) noexcept
    {
        m_Position = DirectX::XMFLOAT3(x, y, z);
        this->Update();
    }

    void Camera::SetPosition(float value) noexcept
    {
        m_Position = DirectX::XMFLOAT3(value, value, value);
        this->Update();
    }

    void Camera::AdjustPosition(const DirectX::XMFLOAT3& distance) noexcept
    {
        m_Position.x += distance.x;
        m_Position.y += distance.y;
        m_Position.z += distance.z;
        this->Update();
    }

    void Camera::AdjustPosition(const DirectX::XMVECTOR& distance) noexcept
    {
        using namespace DirectX;

        auto pos = DirectX::XMVectorSet(m_Position.x, m_Position.y, m_Position.z, 1.0f) + distance;
        DirectX::XMStoreFloat3(&m_Position, pos);
        this->Update();
    }

    void Camera::AdjustPosition(float x, float y, float z) noexcept
    {
        m_Position.x += x;
        m_Position.y += y;
        m_Position.z += z;
        this->Update();
    }

    void Camera::AdjustPosition(float value) noexcept
    {
        m_Position.x += value;
        m_Position.y += value;
        m_Position.z += value;
        this->Update();
    }

    DirectX::XMFLOAT3 Camera::GetRotation() const noexcept
    {
        return m_Rotation;
    }

    DirectX::XMVECTOR Camera::GetRotationVector() const noexcept
    {
        return DirectX::XMLoadFloat3(&m_Rotation);
    }

    DirectX::XMVECTOR Camera::GetUpVector() const noexcept
    {
        return m_Up;
    }

    DirectX::XMVECTOR Camera::GetDownVector() const noexcept
    {
        return m_Down;
    }

    DirectX::XMVECTOR Camera::GetRightVector() const noexcept
    {
        return m_Right;
    }

    DirectX::XMVECTOR Camera::GetLeftVector() const noexcept
    {
        return m_Left;
    }

    DirectX::XMVECTOR Camera::GetForwardVector() const noexcept
    {
        return m_Forward;
    }

    DirectX::XMVECTOR Camera::GetBackwardVector() const noexcept
    {
        return m_Backward;
    }

    void Camera::SetRotation(const DirectX::XMFLOAT3& rotation) noexcept
    {
        m_Rotation = rotation;
        this->Update();
    }

    void Camera::SetRotation(float x, float y, float z) noexcept
    {
        m_Rotation = DirectX::XMFLOAT3(x, y, z);
        this->Update();
    }

    void Camera::SetRotation(float value) noexcept
    {
        m_Rotation = DirectX::XMFLOAT3(value, value, value);
        this->Update();
    }

    void Camera::AdjustRotation(const DirectX::XMFLOAT3& angle) noexcept
    {
        m_Rotation.x += angle.x;
        m_Rotation.y += angle.y;
        m_Rotation.z += angle.z;
        this->Update();
    }

    void Camera::AdjustRotation(const DirectX::XMVECTOR& angle) noexcept
    {
        using namespace DirectX;

        auto ang = DirectX::XMVectorSet(m_Rotation.x, m_Rotation.y, m_Rotation.z, 1.0f) + angle;
        DirectX::XMStoreFloat3(&m_Position, ang);
        this->Update();
    }

    void Camera::AdjustRotation(float value) noexcept
    {
        m_Rotation.x += value;
        m_Rotation.y += value;
        m_Rotation.z += value;
        this->Update();
    }

    void Camera::AdjustRotation(float x, float y, float z) noexcept
    {
        m_Rotation.x += x;
        m_Rotation.y += y;
        m_Rotation.z += z;
        this->Update();
    }

    DirectX::XMMATRIX Camera::GetViewMatrix() const noexcept
    {
        return m_ViewMatrix;
    }

    float Camera::CalculateDistanceBetweenPoints(const DirectX::XMFLOAT3& point1, const DirectX::XMFLOAT3& point2) const noexcept
    {
        return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2) + pow(point2.z - point1.z, 2));
    }

    void Camera::Update() noexcept
    {
        using namespace DirectX;
        XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(
            XMConvertToRadians(m_Rotation.x), 
            XMConvertToRadians(m_Rotation.y), 
            XMConvertToRadians(m_Rotation.z)
        );

        this->m_Forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, rotationMatrix);
        this->m_Backward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, rotationMatrix);
        this->m_Down = XMVector3TransformCoord(this->DEFAULT_DOWN_VECTOR, rotationMatrix);
        this->m_Up = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, rotationMatrix);
        this->m_Left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, rotationMatrix);
        this->m_Right = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, rotationMatrix);

        m_ViewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_Position), XMLoadFloat3(&m_Position) + this->m_Forward, m_Up);
    }
}