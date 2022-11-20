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
		: m_Window(title, width, height), m_Light(m_Window.GetGraphics(), {0.0f, 1000.0f, 1000.0f}, {1.0f, 1.0f, 1.0f, 1.0f}),
		m_SkyBox(m_Window.GetGraphics(), "sandbox\\res\\texture\\sphere.obj", 
			graphics::Texture(m_Window.GetGraphics(), L"sandbox\\res\\texture\\sky.jpg"))
	{
		m_SkyBox.SetOwnPixelShader(L"sandbox\\res\\shaders\\SkyBox.hlsl");
		m_SkyBox.Scale(100.0f);

		m_Window.GetGraphics().SetProjectionMatrix(
			DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, m_Window.GetWidth() / m_Window.GetHeight(), 0.01f, 150.0f)
		);
		m_Window.GetGraphics().Camera.SetPosition({ 0.0f, 0.0f, -10.0f });

		const char* models[] = {
			"sandbox\\res\\texture\\suzanne.obj",
			"sandbox\\res\\texture\\sphere.obj",
			"sandbox\\res\\texture\\Chaynik.obj",
			"sandbox\\res\\texture\\sword.obj",
		};
		const wchar_t* textures[] = {
			L"sandbox\\res\\texture\\stones.bmp",
			L"sandbox\\res\\texture\\BatEye.dds",
			L"sandbox\\res\\texture\\Chaynik.png",
			L"sandbox\\res\\texture\\sword.png",
		};

		std::unique_ptr<graphics::entity::Model> model = nullptr;
		for (uint32_t i = 0; i < ARRAYSIZE(models); ++i) {
			model = std::make_unique<graphics::entity::Model>(m_Window.GetGraphics(), models[i], 
				graphics::Texture(m_Window.GetGraphics(), textures[i]));
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

		m_Window.GetGraphics().ClearBuffers(0.2f, 0.2f, 0.2f);

		m_Window.GetGraphics().SetRasterizerState(false);
		for (auto& drawable : m_Drawables) {
			if (auto p = dynamic_cast<engine::graphics::entity::Model*>(drawable.get())) {
				p->AdjustRotation(0.0f, 15.0f * dt, 0.0f);
			}
			drawable->Draw();
		}

		//if (m_Window.Keyboard.IsKeyPressed('J')) {
		//	m_Light.AdjustPosition(-1000.0f * dt, 0.0f, 0.0f);
		//}
		//if (m_Window.Keyboard.IsKeyPressed('L')) {
		//	m_Light.AdjustPosition(1000.0f * dt, 0.0f, 0.0f);
		//}
		//if (m_Window.Keyboard.IsKeyPressed('I')) {
		//	m_Light.AdjustPosition(0.0f, 1000.0f * dt, 0.0f);
		//}
		//if (m_Window.Keyboard.IsKeyPressed('K')) {
		//	m_Light.AdjustPosition(0.0f, -1000.0f * dt, 0.0f);
		//}
		//m_Light.Bind();

		const XMFLOAT3 ROTATION = m_Window.GetGraphics().Camera.GetRotation();
		const float SPEED = 7.5f * dt;

		if (m_Window.Keyboard.IsKeyPressed('W')) {
			m_Window.GetGraphics().Camera.AdjustPosition(this->m_Window.GetGraphics().Camera.GetForwardVector() * SPEED);
		}
		if (m_Window.Keyboard.IsKeyPressed('S')) {
			m_Window.GetGraphics().Camera.AdjustPosition(this->m_Window.GetGraphics().Camera.GetBackwardVector() * SPEED);
		}

		if (m_Window.Keyboard.IsKeyPressed('A')) {
			m_Window.GetGraphics().Camera.AdjustPosition(this->m_Window.GetGraphics().Camera.GetLeftVector() * SPEED);
		}
		if (m_Window.Keyboard.IsKeyPressed('D')) {
			m_Window.GetGraphics().Camera.AdjustPosition(this->m_Window.GetGraphics().Camera.GetRightVector() * SPEED);
		}

		if (m_Window.Keyboard.IsKeyPressed(VK_SPACE)) {
			m_Window.GetGraphics().Camera.AdjustPosition(0.0f, SPEED, 0.0f);
		}
		if (m_Window.Keyboard.IsKeyPressed(VK_CONTROL)) {
			m_Window.GetGraphics().Camera.AdjustPosition(0.0f, -SPEED, 0.0f);
		}

		if (m_Window.Keyboard.IsKeyPressed(VK_RIGHT)) {
			m_Window.GetGraphics().Camera.AdjustRotation(0.0f, 100 * dt, 0.0f);
		}
		if (m_Window.Keyboard.IsKeyPressed(VK_LEFT)) {
			m_Window.GetGraphics().Camera.AdjustRotation(0.0f, -100 * dt, 0.0f);
		}
		if (m_Window.Keyboard.IsKeyPressed(VK_UP)) {
			m_Window.GetGraphics().Camera.AdjustRotation(-100 * dt, 0.0f, 0.0f);
		}
		if (m_Window.Keyboard.IsKeyPressed(VK_DOWN)) {
			m_Window.GetGraphics().Camera.AdjustRotation(100 * dt, 0.0f, 0.0f);
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
				m_Window.GetGraphics().Camera.AdjustRotation(DY, DX, 0.0f);

				lastCursorPos = currCursorPos;
			}
		}
		else {
			isRotated = false;
		}

		m_Window.GetGraphics().SetRasterizerState(true);
		m_SkyBox.SetPosition(m_Window.GetGraphics().Camera.GetPosition());
		m_SkyBox.Draw();

		m_Window.GetGraphics().SwapBuffers();
	}
}