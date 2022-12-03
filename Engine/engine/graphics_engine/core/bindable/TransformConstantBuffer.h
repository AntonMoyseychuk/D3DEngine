#pragma once
#include "engine/graphics_engine/core/drawable/Drawable.h"
#include "engine/graphics_engine/core/bindable/ConstantBuffer.h"


namespace engine::graphics::core {
	class TransformConstantBuffer : public Bindable
	{
	public:
		struct Transform
		{
			DirectX::XMMATRIX Model;
			DirectX::XMMATRIX View;
			DirectX::XMMATRIX Projection;

			Transform(const DirectX::XMMATRIX& model, const DirectX::XMMATRIX& view, const DirectX::XMMATRIX& proj)
				: Model(model), View(view), Projection(proj)
			{
			}
		};

	public:
		TransformConstantBuffer(const Drawable& parent);
		void Bind() const noexcept override;
	
	private:
		static std::unique_ptr<VSConstantBuffer<Transform>> m_VSConstBuff;
		
		const Drawable& m_Parent;
	};
}