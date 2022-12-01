#include "Application.h"
#include "engine/src/graphics/Graphics.h"

#include "engine/src/graphics/bindable/Bindable.h"

#include "engine/src/graphics/bindable/VertexShader.h"
#include "engine/src/graphics/bindable/PixelShader.h"

#include "engine/src/graphics/drawable/Model.h"

#include <sstream>
#include <iomanip>
#include <DirectXMath.h>

namespace engine::app {
	Application::Application(const wchar_t* title, uint32_t width, uint32_t height)
		: m_Window(title, width, height), m_Light({0.0f, 1000.0f, 1000.0f}, {1.0f, 1.0f, 1.0f, 1.0f}),
		m_SkyBox(graphics::Texture(L"sandbox\\res\\texture\\sky.jpg"))
	{
		m_SkyBox.Scale(100.0f);

		graphics::Graphics::Get().SetProjectionMatrix(
			DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, m_Window.GetWidth() / m_Window.GetHeight(), 0.01f, 150.0f)
		);
		graphics::Graphics::Get().Camera.SetPosition({ 0.0f, 0.0f, -10.0f });

		const char* models[] = {
			//"sandbox\\res\\models\\Chaynik.obj",
			//"sandbox\\res\\models\\sphere.obj",
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

		std::unique_ptr<graphics::entity::Model> model = nullptr;
		for (uint32_t i = 0; i < ARRAYSIZE(models); ++i) {
			model = std::make_unique<graphics::entity::Model>(models[i]/*, graphics::Texture(m_Window.GetGraphics(), textures[i])*/);
			model->SetPosition(i * 5.0f, 0.0f, 0.0f);
		
			m_Drawables.emplace_back(std::move(model));
		}
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
			}
		}
		return msg.wParam;
	}

	void Application::Update()
	{
		using namespace DirectX;

		const float dt = m_Timer.GetDeltaTime();

		std::wostringstream oss;
		oss << m_Window.GetTitle() + std::wstring(L" | FPS: ")
			<< std::setprecision(1) << std::fixed << 1.0f / dt;
		m_Window.SetTitle(oss.str().c_str());

		graphics::Graphics::Get().ClearBuffers(0.2f, 0.2f, 0.2f);

		graphics::Graphics::Get().SetRasterizerState(false);
		for (auto& drawable : m_Drawables) {
			if (auto p = dynamic_cast<graphics::entity::Model*>(drawable.get())) {
				p->AdjustRotation(0.0f, 15.0f * dt, 0.0f);
			}
			drawable->Draw();
		}
		
		graphics::Graphics::Get().SetRasterizerState(true);
		m_SkyBox.SetPosition(graphics::Graphics::Get().Camera.GetPosition());
		m_SkyBox.Draw();
		
		m_Light.Update();
		
		
		//CAMERA LOGIC
		const XMFLOAT3 ROTATION = graphics::Graphics::Get().Camera.GetRotation();
		float SPEED = 7.5f * dt;
		
		if (m_Window.Keyboard.IsKeyPressed('W')) {
			graphics::Graphics::Get().Camera.AdjustPosition(graphics::Graphics::Get().Camera.GetForwardVector() * SPEED);
		}
		if (m_Window.Keyboard.IsKeyPressed('S')) {
			graphics::Graphics::Get().Camera.AdjustPosition(graphics::Graphics::Get().Camera.GetBackwardVector() * SPEED);
		}
		
		if (m_Window.Keyboard.IsKeyPressed('A')) {
			graphics::Graphics::Get().Camera.AdjustPosition(graphics::Graphics::Get().Camera.GetLeftVector() * SPEED);
		}
		if (m_Window.Keyboard.IsKeyPressed('D')) {
			graphics::Graphics::Get().Camera.AdjustPosition(graphics::Graphics::Get().Camera.GetRightVector() * SPEED);
		}
		
		if (m_Window.Keyboard.IsKeyPressed(VK_SPACE)) {
			graphics::Graphics::Get().Camera.AdjustPosition(0.0f, SPEED, 0.0f);
		}
		if (m_Window.Keyboard.IsKeyPressed(VK_CONTROL)) {
			graphics::Graphics::Get().Camera.AdjustPosition(0.0f, -SPEED, 0.0f);
		}
		
		if (m_Window.Keyboard.IsKeyPressed(VK_RIGHT)) {
			graphics::Graphics::Get().Camera.AdjustRotation(0.0f, 100 * dt, 0.0f);
		}
		if (m_Window.Keyboard.IsKeyPressed(VK_LEFT)) {
			graphics::Graphics::Get().Camera.AdjustRotation(0.0f, -100 * dt, 0.0f);
		}
		if (m_Window.Keyboard.IsKeyPressed(VK_UP)) {
			graphics::Graphics::Get().Camera.AdjustRotation(-100 * dt, 0.0f, 0.0f);
		}
		if (m_Window.Keyboard.IsKeyPressed(VK_DOWN)) {
			graphics::Graphics::Get().Camera.AdjustRotation(100 * dt, 0.0f, 0.0f);
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
				graphics::Graphics::Get().Camera.AdjustRotation(DY, DX, 0.0f);
		
				lastCursorPos = currCursorPos;
			}
		}
		else {
			isRotated = false;
		}

		m_Window.SwapBuffers(true);
	}
}