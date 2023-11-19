#pragma once

#include "Shader.h"
#include "Camera.h"


class Renderer {
public:

	/// <summary>
	/// Initialize Renderer in here 
	/// </summary>
	/// <param name="window">= Get GLFWwindow pointer from "Engine" </param>
	Renderer(GLFWwindow* window);


	/// <summary>
	/// Renderer is unique object, Copy is not allowed 
	/// </summary>
	/// <param name="other">= not available </param>
	Renderer(const Renderer& other) = delete;
	/// <summary>
	/// Renderer is unique object, Copy is not allowed
	/// </summary>
	/// <param name="other">= not available </param>
	Renderer& operator=(const Renderer& other) = delete;


private:

	GLFWwindow* m_window{ nullptr };


	/// <summary>
	/// Renderer's Shader 
	/// </summary>
	std::unique_ptr<Shader> m_shader{ nullptr };


	std::unique_ptr<Camera> m_mainCamera{ nullptr };

	UINT temp{};
	size_t temp_size{};


	GLenum m_renderMode = GL_FILL;


public:


	void Render();
	void Update(float DeltaTime);


};

