#pragma once
class Renderer{
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

public:


	void Render();

};

