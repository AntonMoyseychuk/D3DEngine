#pragma once
#include "engine/utility/exception/ExeptionMacros.h"
#include "engine/graphics_engine/core/RenderSystem.h"

#include <DirectXMath.h>
#include <memory>
#include <vector>

namespace graphics_engine::core {
	class Bindable;
	class IndexBuffer;
}

namespace graphics_engine::core::entity {
	template <typename T>
	class GameObject;
}

namespace graphics_engine::core {
	class Drawable
	{
		template <typename T>
		friend class entity::GameObject;
	public:
		Drawable() = default;
		Drawable(const Drawable&) = delete;
		Drawable& operator=(const Drawable&) = delete;

		virtual void Draw() const noexcept;

		virtual DirectX::XMMATRIX GetTransform() const noexcept = 0;

		virtual ~Drawable() = default;

	protected:
		void AddBind(std::unique_ptr<Bindable> bind, std::vector<std::unique_ptr<Bindable>>::iterator where) noexcept;
		void AddIndexBuffer(std::unique_ptr<IndexBuffer> ib) noexcept;

		virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept = 0;
		virtual std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() noexcept = 0;
		const std::vector<std::unique_ptr<Bindable>>& GetBinds() const noexcept;
		std::vector<std::unique_ptr<Bindable>>& GetBinds() noexcept;

	private:
		const graphics_engine::core::IndexBuffer* m_IndexBuffer = nullptr;
		std::vector<std::unique_ptr<Bindable>> m_Binds = {};
	};
}