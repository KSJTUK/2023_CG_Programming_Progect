#include "pch.h"
#include "Input.h"

Input* Input::InputInstance = nullptr;

Input* Input::GetInstance(GLFWwindow* window)
{

	if (InputInstance == nullptr) {
		InputInstance = new Input;

		InputInstance->m_window = window;


		InputInstance->m_keyboard_State = new KEY_STATE[256];
		
		for (auto i = 0; i < 256; ++i) {
			InputInstance->m_keyboard_State[i] = KEY_STATE::NONE;
		}


		double tx_, ty_{};
		glfwGetCursorPos(InputInstance->m_window, &tx_, &ty_);
		InputInstance->m_prevMouse = float2{ static_cast<float>(tx_),static_cast<float>(ty_) };



	}




	return InputInstance;
}

Input* Input::GetInstance()
{
	assert(InputInstance != nullptr);
	return InputInstance;
}

void Input::Update()
{
	
	BYTE temp[256]{ 0, };

	assert(GetKeyboardState(temp));



	for (auto i = 0; i < 256; ++i) {
		if (temp[i] & 0x80) {
			if (m_keyboard_State[i] == KEY_STATE::NONE or m_keyboard_State[i] == KEY_STATE::RELEASED) {
				m_keyboard_State[i] = KEY_STATE::DOWN;
			}
			else if (m_keyboard_State[i] == KEY_STATE::DOWN) {
				m_keyboard_State[i] = KEY_STATE::PRESSED;
			}
		}
		else {
			if (m_keyboard_State[i] == KEY_STATE::PRESSED or m_keyboard_State[i] == KEY_STATE::DOWN) {
				m_keyboard_State[i] = KEY_STATE::RELEASED;
			}
			else if (m_keyboard_State[i] == KEY_STATE::RELEASED) {
				m_keyboard_State[i] = KEY_STATE::NONE;
			}
		}


		if (temp[VK_ESCAPE] & 0x80) {
			glfwSetWindowShouldClose(m_window, GLFW_TRUE);
		}
	}







}

const KEY_STATE Input::Getkey(int key)
{
	return m_keyboard_State[key];
}
