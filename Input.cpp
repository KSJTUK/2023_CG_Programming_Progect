#include "pch.h"
#include "Input.h"

Input* Input::InputInstance = nullptr;


void Input::Init(GLFWwindow* window)
{

	InputInstance->m_window = window;


	InputInstance->m_keyboard_State = new KEY_STATE[256];

	for (auto i = 0; i < 256; ++i) {
		InputInstance->m_keyboard_State[i] = KEY_STATE::NONE;
	}


	double tx_, ty_{};
	glfwGetCursorPos(InputInstance->m_window, &tx_, &ty_);
	InputInstance->m_prevMouse = float2{ static_cast<float>(tx_),static_cast<float>(ty_) };


}



Input* Input::GetInstance()
{
	if (InputInstance == nullptr) {
		InputInstance = new Input();
	}


	return InputInstance;
}


void Input::Update()
{
	
	BYTE temp[256]{ 0, };

	assert(GetKeyboardState(temp));



	for (auto i = 0; i < 256; ++i) {
		if (temp[i] & 0x80) {
			if (m_keyboard_State[i] == KEY_STATE::NONE or m_keyboard_State[i] == KEY_STATE::RELEASE) {
				m_keyboard_State[i] = KEY_STATE::DOWN;
			}
			else if (m_keyboard_State[i] == KEY_STATE::DOWN) {
				m_keyboard_State[i] = KEY_STATE::PRESS;
			}
		}
		else {
			if (m_keyboard_State[i] == KEY_STATE::PRESS or m_keyboard_State[i] == KEY_STATE::DOWN) {
				m_keyboard_State[i] = KEY_STATE::RELEASE;
			}
			else if (m_keyboard_State[i] == KEY_STATE::RELEASE) {
				m_keyboard_State[i] = KEY_STATE::NONE;
			}
		}


	}


	if (temp[VK_ESCAPE] & 0x80) {
		glfwSetWindowShouldClose(m_window, GLFW_TRUE);
	}

	double tx_, ty_;


	glfwGetCursorPos(m_window, &tx_, &ty_);

	m_deltaMouse.x = static_cast<float>(tx_) - m_prevMouse.x;
	m_deltaMouse.y = static_cast<float>(ty_) - m_prevMouse.y;

	m_prevMouse.x = static_cast<float>(tx_);
	m_prevMouse.y = static_cast<float>(ty_);





}

const KEY_STATE Input::GetKey(int key)
{
	return m_keyboard_State[key];
}
