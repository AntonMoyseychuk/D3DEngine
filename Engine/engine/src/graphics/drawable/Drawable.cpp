#include "Drawable.h"
#include "engine/src/graphics/bindable/IndexBuffer.h"

namespace engine::graphics {
	const Graphics* Drawable::m_Graphics = nullptr;

	Drawable::Drawable(const Graphics& gfx)
	{
		if (m_Graphics == nullptr) {
			m_Graphics = &gfx;
		}
	}

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

		m_Graphics->DrawIndexed(m_IndexBuffer->GetIndexCount());
	}

	void Drawable::AddBind(std::unique_ptr<Bindable> bind) noexcept
	{
		if (typeid(*bind) == typeid(IndexBuffer)) {
			THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(E_INVALIDARG, "*Must* use AddIndexBuffer to bind index buffer");
		}
		m_Binds.push_back(std::move(bind));
	}

	void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> ib) noexcept
	{
		if (m_IndexBuffer != nullptr) {
			THROW_ENGINE_D3D_EXCEPTION_MSG_NOINFO(E_INVALIDARG, "Attempting to add index buffer a second time!");
		}

		m_IndexBuffer = ib.get();
		m_Binds.push_back(std::move(ib));
	}
}