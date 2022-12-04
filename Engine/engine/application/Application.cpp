#include "Application.h"

#include "engine/render_system/core/RenderSystem.h"

#include "engine/render_system/core/drawable/Model.h"

#include <sstream>
#include <iomanip>
#include <DirectXMath.h>

namespace engine::app {
	Application::Application(const wchar_t* title, uint32_t width, uint32_t height)
		: Window(title, width, height), 
		Renderer(graphics::core::RenderSystem::Get()), 
		TextureManager(graphics::core::TextureManager::Get()),
		ModelManager(graphics::core::ModelManager::Get())//,
		//m_SkySphere(*m_TextureManager.CreateTextureFromFile(L"sandbox\\res\\texture\\sky.jpg"))
	{
		using namespace graphics::core;

		//m_SkySphere.Scale(100.0f);

		Renderer.SetProjectionMatrix(
			DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, Window.GetWidth() / Window.GetHeight(), 0.01f, 150.0f)
		);
		Renderer.Camera.SetPosition({ 0.0f, 0.0f, -10.0f });
		
		const wchar_t* models[] = {
			//L"sandbox\\res\\models\\Chaynik.obj",
			L"sandbox\\res\\models\\sphere.obj",
			L"sandbox\\res\\models\\suzanne.obj",
			//L"sandbox\\res\\models\\room.obj",
			//L"sandbox\\res\\models\\sword.obj",
		};
		const wchar_t* textures[] = {
			//L"sandbox\\res\\texture\\Chaynik.png",
			//L"sandbox\\res\\texture\\BatEye.dds",
			L"sandbox\\res\\texture\\stones.bmp",
			//L"sandbox\\res\\texture\\sword.png",
		};

		for (uint32_t i = 0; i < ARRAYSIZE(models); ++i) {
			auto model = ModelManager.CreateModelFromFile(models[i]);
			model->SetPosition(i * 5.0f, 0.0f, 0.0f);
		
			m_Drawables.emplace_back(std::move(model));
		}

		//
		//m_Lights.emplace_back(std::move(std::make_unique<entity::Light>(DirectX::XMFLOAT3(0.0f, 1000.0f, 1000.0f),
		//	DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)))
		//);
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
		Window.ClearBuffers(0.2f, 0.2f, 0.2f);

		//m_Renderer.SetRasterizerState(true);
		//m_SkySphere.Draw();

		Renderer.SetRasterizerState(false);
		for (auto& drawable : m_Drawables) {
			drawable->Draw();
		}

		Window.SwapBuffers(true);
	}

	void Application::Update()
	{
		using namespace DirectX;
		using namespace graphics::core;

		const float dt = Timer.GetDeltaTime();

		std::wostringstream oss;
		oss << Window.GetTitle() + std::wstring(L" | FPS: ")
			<< std::setprecision(1) << std::fixed << 1.0f / dt;
		Window.SetTitle(oss.str().c_str());


		for (auto& drawable : m_Drawables) {
			if (auto p = std::static_pointer_cast<Model>(drawable)) {
				p->AdjustRotation(0.0f, 15.0f * dt, 0.0f);
			}
		}
		
		//
		//for (auto& light : m_Lights) {
		//	light->Update();
		//}
		
		//m_SkySphere.SetPosition(m_Renderer.Camera.GetPosition());
		
		
		//CAMERA LOGIC
		{
			const XMFLOAT3 ROTATION = Renderer.Camera.GetRotation();
			float SPEED = 7.5f * dt;

			if (Window.Keyboard.IsKeyPressed('W')) {
				Renderer.Camera.AdjustPosition(Renderer.Camera.GetForwardVector() * SPEED);
			}
			if (Window.Keyboard.IsKeyPressed('S')) {
				Renderer.Camera.AdjustPosition(Renderer.Camera.GetBackwardVector() * SPEED);
			}

			if (Window.Keyboard.IsKeyPressed('A')) {
				Renderer.Camera.AdjustPosition(Renderer.Camera.GetLeftVector() * SPEED);
			}
			if (Window.Keyboard.IsKeyPressed('D')) {
				Renderer.Camera.AdjustPosition(Renderer.Camera.GetRightVector() * SPEED);
			}

			if (Window.Keyboard.IsKeyPressed(VK_SPACE)) {
				Renderer.Camera.AdjustPosition(0.0f, SPEED, 0.0f);
			}
			if (Window.Keyboard.IsKeyPressed(VK_CONTROL)) {
				Renderer.Camera.AdjustPosition(0.0f, -SPEED, 0.0f);
			}

			if (Window.Keyboard.IsKeyPressed(VK_RIGHT)) {
				Renderer.Camera.AdjustRotation(0.0f, 100 * dt, 0.0f);
			}
			if (Window.Keyboard.IsKeyPressed(VK_LEFT)) {
				Renderer.Camera.AdjustRotation(0.0f, -100 * dt, 0.0f);
			}
			if (Window.Keyboard.IsKeyPressed(VK_UP)) {
				Renderer.Camera.AdjustRotation(-100 * dt, 0.0f, 0.0f);
			}
			if (Window.Keyboard.IsKeyPressed(VK_DOWN)) {
				Renderer.Camera.AdjustRotation(100 * dt, 0.0f, 0.0f);
			}

			static bool isRotated;
			static std::pair<float, float> lastCursorPos, currCursorPos;

			if (Window.Mouse.IsLeftButtonPressed()) {
				if (!isRotated) {
					lastCursorPos = Window.Mouse.GetPosition();
					isRotated = true;
				}
				else {
					currCursorPos = Window.Mouse.GetPosition();
					const float DX = (currCursorPos.first - lastCursorPos.first) / 2.5f;
					const float DY = (currCursorPos.second - lastCursorPos.second) / 2.5f;
					Renderer.Camera.AdjustRotation(DY, DX, 0.0f);

					lastCursorPos = currCursorPos;
				}
			}
			else {
				isRotated = false;
			}
		}
	}
}