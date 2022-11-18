#include "DXGIInfoManager.h"

#include "engine/src/window/Window.h"
#include "engine/src/utility/exception/D3DException.h"
#include "engine/src/utility/exception/WindowException.h"

#include <memory>

#pragma comment(lib, "dxguid.lib")

#define THROW_D3D_EXCEPTION_NOINFO(hResult) if (FAILED((D3D_OP_RESULT = (hResult))))\
	throw ENGINE_D3D_EXCEPTION(D3D_OP_RESULT, std::vector<std::string>())

namespace engine::util {
	DXGIInfoManager::DXGIInfoManager()
	{
		//typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);
		//auto hModDxgiDebug = LoadLibraryEx(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
		//if (hModDxgiDebug == nullptr) {
		//	throw ENGINE_WINDOW_LAST_ERROR_EXCEPTION();
		//}
		//
		//const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
		//	reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface"))
		//);
		//if (DxgiGetDebugInterface == nullptr)
		//{
		//	throw ENGINE_WINDOW_LAST_ERROR_EXCEPTION();
		//}
		//
		//HRESULT D3D_OP_RESULT;
		//THROW_D3D_EXCEPTION_NOINFO(DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &m_DXGIInfoQueue));
	}

	void DXGIInfoManager::Reset() const noexcept
	{
		// set the index (next) so that the next all to GetMessages()
		// will only get errors generated after this call
		//m_Next = m_DXGIInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	}

	std::vector<std::string> DXGIInfoManager::GetMessages() const
	{
		std::vector<std::string> messages;
		//const auto end = m_DXGIInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
		//for (auto i = m_Next; i < end; i++)
		//{
		//	HRESULT D3D_OP_RESULT;
		//	SIZE_T messageLength;
		//	// get the size of message i in bytes
		//	THROW_D3D_EXCEPTION_NOINFO(m_DXGIInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength));
		//	// allocate memory for message
		//	auto bytes = std::make_unique<uint8_t[]>(messageLength);
		//	auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		//	// get the message and push its description into the vector
		//	THROW_D3D_EXCEPTION_NOINFO(m_DXGIInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength));
		//	messages.push_back(pMessage->pDescription);
		//}
		return messages;
	}
};