#include "pch.h"
#include "Camera.h"
#include "Input.h"

Camera::Camera(GLFWwindow* Window, UINT ShaderId, glm::vec3 EYE, float NearZ, float FarZ)
	: m_window(Window), m_shaderId(ShaderId), m_eye(EYE), m_nearZ(NearZ), m_farZ(FarZ)
{
	int w, h;

	glfwGetFramebufferSize(m_window, &w, &h);

	m_aspect = static_cast<float>(w) / static_cast<float>(h);


	m_projectionLocation = glGetUniformLocation(m_shaderId, "perspective");
	m_lookatLocation = glGetUniformLocation(m_shaderId, "lookat");


	m_basisZ = glm::normalize(-m_at);
	m_basisX = glm::normalize(glm::cross(m_up, m_basisZ));
	m_basisY = glm::cross(m_basisZ, m_basisX);




}


void Camera::Update(float DeltaTime){

	int w, h;
	glfwGetFramebufferSize(m_window, &w, &h);
	m_aspect = static_cast<float>(w) / static_cast<float>(h);

	
	if (Input::GetInstance()->GetKey(GLFW_KEY_W) == KEY_STATE::PRESS) {
		m_eye -= m_basisZ * DeltaTime * 5.f;
	}


	if (Input::GetInstance()->GetKey(GLFW_KEY_S) == KEY_STATE::PRESS) {
		m_eye += m_basisZ * DeltaTime * 5.f;
	}


	if (Input::GetInstance()->GetKey(GLFW_KEY_A) == KEY_STATE::PRESS) {
		m_eye -= m_basisX * DeltaTime * 5.f;
	}


	if (Input::GetInstance()->GetKey(GLFW_KEY_D) == KEY_STATE::PRESS) {
		m_eye += m_basisX * DeltaTime * 5.f;
	}

	if (Input::GetInstance()->GetKey(GLFW_KEY_Q) == KEY_STATE::PRESS) {
		m_eye -= m_basisY * DeltaTime * 5.f;

	}


	if (Input::GetInstance()->GetKey(GLFW_KEY_E) == KEY_STATE::PRESS) {
		m_eye += m_basisY * DeltaTime * 5.f;

	}


	float2 deltaMouse = Input::GetInstance()->GetDeltaMouse();

	if (!(deltaMouse.x == 0 and deltaMouse.y == 0)) {

		glm::mat4 cameraRotate{ 1.f };


		cameraRotate = glm::rotate(cameraRotate, glm::radians(-deltaMouse.y  * MOUSE_SENSITIVE), m_basisX);
		cameraRotate = glm::rotate(cameraRotate, glm::radians(-deltaMouse.x  * MOUSE_SENSITIVE), m_basisY);

		m_at = glm::normalize(glm::vec3(cameraRotate * glm::vec4(m_at, 1.f)));


		m_basisZ = glm::normalize(-m_at);
		m_basisX = glm::normalize(glm::cross(m_up, m_basisZ));
		m_basisY = glm::cross(m_basisZ, m_basisX);



	}


}

void Camera::Render(){


	//auto p{ glm::mat4(1.f) };
	auto p{ glm::perspective(glm::radians(m_fovY), m_aspect, m_nearZ, m_farZ) };
	glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, glm::value_ptr(
		p)
	);


	//auto v{ glm::mat4{1.f} };
	auto v{ glm::lookAt(m_eye, m_eye + m_at , m_up) };
	glUniformMatrix4fv(m_lookatLocation, 1, GL_FALSE, glm::value_ptr(
		v)
	);




}