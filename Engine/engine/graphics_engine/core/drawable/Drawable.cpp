#include "Drawable.h"
#include "engine/graphics_engine/core/bindable/IndexBuffer.h"

namespace graphics_engine::core {
	const std::vector<std::unique_ptr<Bindable>>& Drawable::GetBinds() const noexcept
	{
		return m_Binds;
	}

	std::vector<std::unique_ptr<Bindable>>& Drawable::GetBinds() noexcept
	{
		return m_Binds;
	}

	void Drawable::Draw() const noexcept
	{
		for (const auto& bind : m_Binds) {
			bind->Bind();
		}

		for (const auto& bind : GetStaticBinds()) {
			bind->Bind();
		}

		RenderSystem::Get().DrawIndexed(m_IndexBuffer->GetIndexCount());
	}

	void Drawable::AddBind(std::unique_ptr<Bindable> bind, std::vector<std::unique_ptr<Bindable>>::iterator where) noexcept
	{
		THROW_EXCEPTION_IF_LOGIC_ERROR(typeid(*bind) == typeid(IndexBuffer), "DRAWABLE", 
			"*Must* use AddIndexBuffer to bind index buffer");
		m_Binds.insert(where, std::move(bind));
	}

	void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> ib) noexcept
	{
		THROW_EXCEPTION_IF_LOGIC_ERROR(m_IndexBuffer != nullptr, "DRAWABLE",
			"Attempting to add index buffer a second time!");

		m_IndexBuffer = ib.get();
		m_Binds.insert(m_Binds.begin(), std::move(ib));
	}
}