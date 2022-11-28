#pragma once
#include "engine/src/graphics/Graphics.h"
#include "engine/src/utility/exception/ExeptionMacros.h"

#include <DirectXMath.h>
#include <memory>

namespace engine::graphics {
	class Bindable;
	class IndexBuffer;
}

namespace engine::graphics::entity {
	template <typename T>
	class Entity;
}

namespace engine::graphics {
	class Drawable
	{
		template <typename T>
		friend class entity::Entity;
	public:
		Drawable(const Graphics& gfx);
		Drawable(const Drawable&) = delete;

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

	protected:
		static const Graphics* m_Graphics;

	private:
		const engine::graphics::IndexBuffer* m_IndexBuffer = nullptr;
		std::vector<std::unique_ptr<Bindable>> m_Binds = {};
	};
}