#pragma once
#include <vector>
#include "Buffer.h"

namespace engine::graphics::core {
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(const std::vector<uint32_t>& indices);

		void Bind() const noexcept override;

		uint32_t GetIndexCount() const;
		const char* GetType() const noexcept override;
	};
}