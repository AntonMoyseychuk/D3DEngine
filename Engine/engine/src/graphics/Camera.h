#pragma once
#include "engine/src/window/Window.h"
#include "engine/src/utility/exception/WindowException.h"

#include <DirectXMath.h>

namespace engine::camera {
    class Camera
    {
    public:
        Camera(const DirectX::XMFLOAT3& position = { 0.0f, 0.0f, 0.0f }, const DirectX::XMFLOAT3& rotation = { 0.0f, 0.0f, 0.0f });

        void SetPosition(const DirectX::XMFLOAT3& position) noexcept;
        void SetPosition(float x, float y, float z) noexcept;
        void SetPosition(float value) noexcept;
        void AdjustPosition(const DirectX::XMFLOAT3& distance) noexcept;
        void AdjustPosition(const DirectX::XMVECTOR& distance) noexcept;
        void AdjustPosition(float x, float y, float z) noexcept;
        void AdjustPosition(float value) noexcept;
        DirectX::XMFLOAT3 GetPosition() const noexcept;
        DirectX::XMVECTOR GetPositionVector() const noexcept;

        void SetRotation(const DirectX::XMFLOAT3& rotation) noexcept;
        void SetRotation(float x, float y, float z) noexcept;
        void SetRotation(float value) noexcept;
        void AdjustRotation(const DirectX::XMFLOAT3& angle) noexcept;
        void AdjustRotation(const DirectX::XMVECTOR& angle) noexcept;
        void AdjustRotation(float x, float y, float z) noexcept;
        void AdjustRotation(float value) noexcept;
        DirectX::XMFLOAT3 GetRotation() const noexcept;
        DirectX::XMVECTOR GetRotationVector() const noexcept;

        DirectX::XMVECTOR GetUpVector() const noexcept;
        DirectX::XMVECTOR GetDownVector() const noexcept;
        DirectX::XMVECTOR GetRightVector() const noexcept;
        DirectX::XMVECTOR GetLeftVector() const noexcept;
        DirectX::XMVECTOR GetForwardVector() const noexcept;
        DirectX::XMVECTOR GetBackwardVector() const noexcept;

        DirectX::XMMATRIX GetViewMatrix() const noexcept;

    protected:
        float CalculateDistanceBetweenPoints(const DirectX::XMFLOAT3& point1, const DirectX::XMFLOAT3& point2) const noexcept;
        void Update() noexcept;

    private:
        static const DirectX::XMVECTOR DEFAULT_BACKWARD_VECTOR;
        static const DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR;
        static const DirectX::XMVECTOR DEFAULT_RIGHT_VECTOR;
        static const DirectX::XMVECTOR DEFAULT_LEFT_VECTOR;
        static const DirectX::XMVECTOR DEFAULT_DOWN_VECTOR;
        static const DirectX::XMVECTOR DEFAULT_UP_VECTOR;

    private:
        DirectX::XMFLOAT3 m_Position;
        DirectX::XMFLOAT3 m_Rotation;

        DirectX::XMVECTOR m_Right;
        DirectX::XMVECTOR m_Left;
        DirectX::XMVECTOR m_Forward;
        DirectX::XMVECTOR m_Backward;
        DirectX::XMVECTOR m_Up;
        DirectX::XMVECTOR m_Down;

        DirectX::XMMATRIX m_ViewMatrix;
    };
}

