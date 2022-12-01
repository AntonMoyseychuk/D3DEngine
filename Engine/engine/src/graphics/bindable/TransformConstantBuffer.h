#pragma once
#include "engine/src/graphics/drawable/Drawable.h"
#include "engine/src/graphics/bindable/ConstantBuffer.h"


namespace engine::graphics {
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