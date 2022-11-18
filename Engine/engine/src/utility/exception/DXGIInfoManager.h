#pragma once
#include <dxgidebug.h>
#include <vector>
#include <string>
#include <wrl.h>

namespace engine::util {
	class DXGIInfoManager
	{
	public:
		DXGIInfoManager();
		~DXGIInfoManager() = default;

		DXGIInfoManager(const DXGIInfoManager&) = delete;
		DXGIInfoManager& operator=(const DXGIInfoManager&) = delete;

		void Reset() const noexcept;
		std::vector<std::string> GetMessages() const;

	private:
		mutable uint64_t m_Next = 0u;
		Microsoft::WRL::ComPtr<IDXGIInfoQueue> m_DXGIInfoQueue = nullptr;
	};
};