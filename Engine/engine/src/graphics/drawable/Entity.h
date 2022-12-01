#pragma once
#include "Drawable.h"
#include "engine/src/graphics/camera/Camera.h"

#include <vector>

namespace engine::graphics::entity {
	template <typename T>
	class Entity : public Drawable
	{
	public:
		void SetPosition(const DirectX::XMFLOAT3& position) noexcept
		{
			m_Position = position;
		}
		void SetPosition(const DirectX::XMVECTOR& position) noexcept
		{
			DirectX::XMStoreFloat3(&m_Position, position);
		}
		void SetPosition(float x, float y, float z) noexcept
		{
			m_Position.x = x;
			m_Position.y = y;
			m_Position.z = z;
		}
		void SetPosition(float value) noexcept
		{
			m_Position.x = value;
			m_Position.y = value;
			m_Position.z = value;
		}
		void AdjustPosition(const DirectX::XMFLOAT3& offset) noexcept
		{
			m_Position.x += offset.x;
			m_Position.y += offset.y;
			m_Position.z += offset.z;
		}
		void AdjustPosition(const DirectX::XMVECTOR& offset) noexcept
		{
			using namespace DirectX;
			auto pos = XMLoadFloat3(&m_Position) + offset;
			XMStoreFloat3(&m_Position, pos);
		}
		void AdjustPosition(float x, float y, float z) noexcept
		{
			m_Position.x += x;
			m_Position.y += y;
			m_Position.z += z;
		}
		void AdjustPosition(float value) noexcept
		{
			m_Position.x += value;
			m_Position.y += value;
			m_Position.z += value;
		}
		DirectX::XMFLOAT3 GetPosition() const noexcept
		{
			return m_Position;
		}
		DirectX::XMVECTOR GetPositionVector() const noexcept
		{
			return DirectX::XMLoadFloat3(&m_Position);
		}

		
		void SetRotation(const DirectX::XMFLOAT3& rotation) noexcept
		{
			m_RotationAngle = rotation;
		}
		void SetRotation(const DirectX::XMVECTOR& rotation) noexcept
		{
			DirectX::XMStoreFloat3(&m_RotationAngle, rotation);
		}
		void SetRotation(float x, float y, float z) noexcept
		{
			m_RotationAngle.x = x;
			m_RotationAngle.y = y;
			m_RotationAngle.z = z;
		}
		void SetRotation(float value) noexcept
		{
			m_RotationAngle.x = value;
			m_RotationAngle.y = value;
			m_RotationAngle.z = value;
		}
		void AdjustRotation(const DirectX::XMFLOAT3& angle) noexcept
		{
			m_RotationAngle.x += angle.x;
			m_RotationAngle.y += angle.y;
			m_RotationAngle.z += angle.z;
		}
		void AdjustRotation(const DirectX::XMVECTOR& angle) noexcept
		{
			using namespace DirectX;
			auto rotation = XMLoadFloat3(&m_RotationAngle) + angle;
			XMStoreFloat3(&m_RotationAngle, rotation);
		}
		void AdjustRotation(float x, float y, float z) noexcept
		{
			m_RotationAngle.x += x;
			m_RotationAngle.y += y;
			m_RotationAngle.z += z;
		}
		void AdjustRotation(float value) noexcept
		{
			m_RotationAngle.x += value;
			m_RotationAngle.y += value;
			m_RotationAngle.z += value;
		}
		DirectX::XMFLOAT3 GetRotation() const noexcept
		{
			return m_RotationAngle;
		}
		DirectX::XMVECTOR GetRotationVector() const noexcept
		{
			return DirectX::XMLoadFloat(&m_RotationAngle);
		}


		void Scale(const DirectX::XMFLOAT3& scale) noexcept
		{
			m_Scale = scale;
		}
		void Scale(float x, float y, float z) noexcept
		{
			m_Scale.x = x;
			m_Scale.y = y;
			m_Scale.z = z;
		}
		void Scale(float value) noexcept
		{
			m_Scale.x = value;
			m_Scale.y = value;
			m_Scale.z = value;
		}
		DirectX::XMFLOAT3 GetScale() const noexcept
		{
			return m_Scale;
		}
		DirectX::XMVECTOR GetScaleVector() const noexcept
		{
			return DirectX::XMLoadFloat3(&m_Scale);
		}


		DirectX::XMMATRIX GetTransform() const noexcept override
		{
			return DirectX::XMMatrixIdentity()
				* DirectX::XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z)
				* DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_RotationAngle.x))
				* DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_RotationAngle.y))
				* DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_RotationAngle.z))
				* DirectX::XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
		}

	protected:
		Entity(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT3& scale, const DirectX::XMFLOAT3& rotation)
			: Drawable(), m_Position(position), m_Scale(scale), m_RotationAngle(rotation)
		{
		}

		static bool IsStaticInitialized() noexcept
		{
			return !m_StaticBinds.empty();
		}

		static void AddStaticBind(std::unique_ptr<Bindable> bind, std::vector<std::unique_ptr<Bindable>>::iterator where = m_StaticBinds.end())
		{
			THROW_EXCEPTION_IF_LOGIC_ERROR(typeid(*bind) == typeid(IndexBuffer), "ENTITY",
				"*Must* use AddStaticIndexBuffer to bind index buffer");
			m_StaticBinds.insert(where, std::move(bind));
		}

		void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> ib) noexcept
		{
			THROW_EXCEPTION_IF_LOGIC_ERROR(m_IndexBuffer != nullptr, "ENTITY", "Attempting to add index buffer a second time!");

			m_IndexBuffer = ib.get();
			m_StaticBinds.insert(m_StaticBinds.begin(), std::move(ib));
		}

		void SetIndexBufferFromStatic() noexcept
		{
			THROW_EXCEPTION_IF_LOGIC_ERROR(m_IndexBuffer != nullptr, "ENTITY", "Attempting to add index buffer a second time!");

			for (const auto& bind : m_StaticBinds) {
				if (const auto p = dynamic_cast<IndexBuffer*>(bind.get())) {
					m_IndexBuffer = p;
					return;
				}
			}

			THROW_EXCEPTION_IF_LOGIC_ERROR(m_IndexBuffer == nullptr, "ENTITY", "Failed to find Index Buffer in static binds!");
		}

	protected:
		inline const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept override
		{
			return m_StaticBinds;
		}

		inline std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() noexcept override
		{
			return m_StaticBinds;
		}

	private:
		static std::vector<std::unique_ptr<Bindable>> m_StaticBinds;

	protected:
		DirectX::XMFLOAT3 m_Position;
		DirectX::XMFLOAT3 m_Scale;
		DirectX::XMFLOAT3 m_RotationAngle;
	};

	template <typename T>
	std::vector<std::unique_ptr<Bindable>> Entity<T>::m_StaticBinds;
}