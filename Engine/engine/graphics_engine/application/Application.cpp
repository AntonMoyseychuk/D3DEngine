#include "Application.h"

#include "engine/graphics_engine/core/RenderSystem.h"

#include "engine/graphics_engine/core/drawable/Model.h"

#include <sstream>
#include <iomanip>
#include <DirectXMath.h>

namespace graphics_engine::app {
	Application::Application(const wchar_t* title, uint32_t width, uint32_t height)
		: m_Window(title, width, height), m_SkySphere(core::Texture(L"sandbox\\res\\texture\\sky.jpg"))
	{
		using namespace core;

		m_SkySphere.Scale(100.0f);

		RenderSystem::Get().SetProjectionMatrix(
			DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, m_Window.GetWidth() / m_Window.GetHeight(), 0.01f, 150.0f)
		);
		RenderSystem::Get().Camera.SetPosition({ 0.0f, 0.0f, -10.0f });
		
		const char* models[] = {
			//"sandbox\\res\\models\\Chaynik.obj",
			"sandbox\\res\\models\\sphere.obj",
			"sandbox\\res\\models\\suzanne.obj",
			//"sandbox\\res\\models\\room.obj",
			//"sandbox\\res\\models\\sword.obj",
		};
		const wchar_t* textures[] = {
			//L"sandbox\\res\\texture\\Chaynik.png",
			//L"sandbox\\res\\texture\\BatEye.dds",
			L"sandbox\\res\\texture\\stones.bmp",
			//L"sandbox\\res\\texture\\sword.png",
		};

		std::unique_ptr<entity::Model> model = nullptr;
		for (uint32_t i = 0; i < ARRAYSIZE(models); ++i) {
			model = std::make_unique<entity::Model>(models[i], Texture(textures[0]));
			model->SetPosition(i * 5.0f, 0.0f, 0.0f);
		
			m_Drawables.emplace_back(std::move(model));
		}

		//
		m_Lights.emplace_back(std::move(std::make_unique<entity::Light>(DirectX::XMFLOAT3(0.0f, 1000.0f, 1000.0f),
			DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)))
		);
	}

	int Application::Run()
	{
		MSG msg = { 0 };

		while (msg.message != WM_QUIT) {
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				Update();
				Render();
			}
		}
		return msg.wParam;
	}

	void Application::Render() const noexcept
	{
		m_Window.ClearBuffers(0.2f, 0.2f, 0.2f);

		core::RenderSystem::Get().SetRasterizerState(true);
		m_SkySphere.Draw();

		core::RenderSystem::Get().SetRasterizerState(false);
		for (auto& drawable : m_Drawables) {
			drawable->Draw();
		}

		m_Window.SwapBuffers(true);
	}

	void Application::Update()
	{
		using namespace DirectX;
		using namespace core;

		const float dt = m_Timer.GetDeltaTime();

		std::wostringstream oss;
		oss << m_Window.GetTitle() + std::wstring(L" | FPS: ")
			<< std::setprecision(1) << std::fixed << 1.0f / dt;
		m_Window.SetTitle(oss.str().c_str());


		for (auto& drawable : m_Drawables) {
			if (auto p = dynamic_cast<entity::Model*>(drawable.get())) {
				p->AdjustRotation(0.0f, 15.0f * dt, 0.0f);
			}
		}
		
		//
		for (auto& light : m_Lights) {
			light->Update();
		}
		
		m_SkySphere.SetPosition(RenderSystem::Get().Camera.GetPosition());
		
		
		//CAMERA LOGIC
		{
			const XMFLOAT3 ROTATION = RenderSystem::Get().Camera.GetRotation();
			float SPEED = 7.5f * dt;

			if (m_Window.Keyboard.IsKeyPressed('W')) {
				RenderSystem::Get().Camera.AdjustPosition(RenderSystem::Get().Camera.GetForwardVector() * SPEED);
			}
			if (m_Window.Keyboard.IsKeyPressed('S')) {
				RenderSystem::Get().Camera.AdjustPosition(RenderSystem::Get().Camera.GetBackwardVector() * SPEED);
			}

			if (m_Window.Keyboard.IsKeyPressed('A')) {
				RenderSystem::Get().Camera.AdjustPosition(RenderSystem::Get().Camera.GetLeftVector() * SPEED);
			}
			if (m_Window.Keyboard.IsKeyPressed('D')) {
				RenderSystem::Get().Camera.AdjustPosition(RenderSystem::Get().Camera.GetRightVector() * SPEED);
			}

			if (m_Window.Keyboard.IsKeyPressed(VK_SPACE)) {
				RenderSystem::Get().Camera.AdjustPosition(0.0f, SPEED, 0.0f);
			}
			if (m_Window.Keyboard.IsKeyPressed(VK_CONTROL)) {
				RenderSystem::Get().Camera.AdjustPosition(0.0f, -SPEED, 0.0f);
			}

			if (m_Window.Keyboard.IsKeyPressed(VK_RIGHT)) {
				RenderSystem::Get().Camera.AdjustRotation(0.0f, 100 * dt, 0.0f);
			}
			if (m_Window.Keyboard.IsKeyPressed(VK_LEFT)) {
				RenderSystem::Get().Camera.AdjustRotation(0.0f, -100 * dt, 0.0f);
			}
			if (m_Window.Keyboard.IsKeyPressed(VK_UP)) {
				RenderSystem::Get().Camera.AdjustRotation(-100 * dt, 0.0f, 0.0f);
			}
			if (m_Window.Keyboard.IsKeyPressed(VK_DOWN)) {
				RenderSystem::Get().Camera.AdjustRotation(100 * dt, 0.0f, 0.0f);
			}

			static bool isRotated;
			static std::pair<float, float> lastCursorPos, currCursorPos;

			if (m_Window.Mouse.IsLeftButtonPressed()) {
				if (!isRotated) {
					lastCursorPos = m_Window.Mouse.GetPosition();
					isRotated = true;
				}
				else {
					currCursorPos = m_Window.Mouse.GetPosition();
					const float DX = (currCursorPos.first - lastCursorPos.first) / 2.5f;
					const float DY = (currCursorPos.second - lastCursorPos.second) / 2.5f;
					RenderSystem::Get().Camera.AdjustRotation(DY, DX, 0.0f);

					lastCursorPos = currCursorPos;
				}
			}
			else {
				isRotated = false;
			}
		}
	}
}