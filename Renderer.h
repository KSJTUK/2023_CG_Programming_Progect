#pragma once

#include "Shader.h"
#include "Camera.h"
#include "Rigidbody.h"

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



	std::unordered_map<std::string,std::shared_ptr<Mesh>> m_meshDict{};

	std::vector<std::shared_ptr<Object>> m_objectList{};




	GLenum m_renderMode = GL_FILL;




private:



	std::shared_ptr<Mesh> testmesh{ nullptr };
	



public:


	void Render();
	void Update(float DeltaTime);


};

