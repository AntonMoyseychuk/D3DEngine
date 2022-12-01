#pragma once
#include "Buffer.h"

namespace engine::graphics {
	class IndexBuffer : public Buffer<uint32_t>
	{
	public:
		IndexBuffer(const std::vector<uint32_t>& indices);

		void Bind() const noexcept override;

		uint32_t GetIndexCount() const;
		const char* GetType() const noexcept override;
	};
}