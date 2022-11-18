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
		: m_Window(title, width, height)
	{
		m_Window.GetGraphics().SetProjectionMatrix(
			DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, m_Window.GetWidth() / m_Window.GetHeight(), 0.01f, 150.0f)
		);
		m_Window.GetGraphics().Camera.SetPosition({ 0.0f, 0.0f, -20.0f });

		const char* models[] = {
			"D:\\Studies\\Graphics\\D3DEngine\\Engine\\sandbox\\res\\texture\\Chaynik.obj",
			"D:\\Studies\\Graphics\\D3DEngine\\Engine\\sandbox\\res\\texture\\sphere.obj",
			"D:\\Studies\\Graphics\\D3DEngine\\Engine\\sandbox\\res\\texture\\sword.obj",
		};
		const wchar_t* textures[] = {
			L"D:\\Studies\\Graphics\\D3DEngine\\Engine\\sandbox\\res\\texture\\Chaynik.png",
			L"D:\\Studies\\Graphics\\D3DEngine\\Engine\\sandbox\\res\\texture\\stones.bmp",
			L"D:\\Studies\\Graphics\\D3DEngine\\Engine\\sandbox\\res\\texture\\sword.png",
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

		for (auto& drawable : m_Drawables) {
			if (auto p = dynamic_cast<engine::graphics::entity::Model*>(drawable.get())) {
				p->AdjustRotation(0.0f, 15.0f * dt, 0.0f);
			}
			drawable->Draw();
		}


		//m_Camera.OnUpdate();
		//{
		//	using namespace DirectX;
		//	static std::pair<float, float> lastCursorPos, currCursorPos;
		//
		//	if (m_Window.Keyboard.IsKeyPressed(VK_MENU)) {
		//		if (m_Window.Mouse.IsLeftButtonPressed()) {
		//			if (!m_Camera.IsRotated()) {
		//				m_IsCameraRotated = true;
		//				lastCursorPos = m_Window.Mouse.GetPosition();
		//			}
		//			else {
		//				currCursorPos = m_Window.Mouse.GetPosition();
		//
		//				float xOffset = currCursorPos.second - lastCursorPos.second;
		//				m_RotationAngle.x = static_cast<int32_t>(m_RotationAngle.x + xOffset * (m_Sensitivity / 10.0f)) % 360;
		//
		//				float yOffset = (m_RotationAngle.x >= -360.0f && m_RotationAngle.x <= -270.0f
		//					|| m_RotationAngle.x >= -90.0f && m_RotationAngle.x <= 90.0f
		//					|| m_RotationAngle.x >= 270.0f && m_RotationAngle.x <= 360.0f) ?
		//					(currCursorPos.first - lastCursorPos.first) : -(currCursorPos.first - lastCursorPos.first);
		//				m_RotationAngle.y = static_cast<int32_t>(m_RotationAngle.y - yOffset * (m_Sensitivity / 10.0f)) % 360;
		//
		//				lastCursorPos = currCursorPos;
		//			}
		//		}
		//		else {
		//			m_IsCameraRotated = false;
		//		}
		//
		//		m_Radius -= m_Window.Mouse.GetScrollDelta() * m_ScrollSensitivity;
		//		if (m_Radius <= 0.0f) {
		//			m_Radius = 0.01f;
		//		}
		//	}
		//
		//	XMStoreFloat3(&m_Position, XMVectorSet(
		//		m_Radius * cos(XMConvertToRadians(m_RotationAngle.y)) * cos(XMConvertToRadians(m_RotationAngle.x)),
		//		m_Radius * sin(XMConvertToRadians(m_RotationAngle.x)),
		//		m_Radius * cos(XMConvertToRadians(m_RotationAngle.x)) * sin(XMConvertToRadians(m_RotationAngle.y)),
		//		1.0f)
		//	);
		//
		//	XMStoreFloat3(&m_Up, XMVector3Normalize(XMVectorSet(
		//		cos(XMConvertToRadians(m_RotationAngle.y)) * cos(XMConvertToRadians(m_RotationAngle.x + 90.0f)),
		//		sin(XMConvertToRadians(m_RotationAngle.x + 90.0f)),
		//		cos(XMConvertToRadians(m_RotationAngle.x + 90.0f)) * sin(XMConvertToRadians(m_RotationAngle.y)),
		//		1.0f)
		//	));
		//}

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

		m_Window.GetGraphics().SwapBuffers();
	}
}