#pragma once
constexpr auto MOUSE_SENSITIVE = 0.1f;


class Camera {
public:
	/// <summary>
	/// Initialize Camera 
	/// </summary>
	/// <param name="Window">Main Window Pointer</param>
	/// <param name="ShaderId">Main Shader ID </param>
	/// <param name="EYE">Camera's Position</param>
	/// <param name="NearZ">Camera's near Z limit </param>
	/// <param name="FarZ">Camera's far Z limit</param>
	Camera(GLFWwindow* Window, UINT ShaderId, glm::vec3 EYE, float NearZ, float FarZ);


	~Camera() = default;


	/// <summary>
	/// Camera is Unique Object, so Copy is not allowed 
	/// </summary>
	/// <param name="other"> : N/A</param>
	Camera(const Camera& other) = delete;
	/// <summary>
	/// Camera is Unique Object, so Copy is not allowed 
	/// </summary>
	/// <param name="other"> : N/A</param>
	Camera& operator=(const Camera& other) = delete;

private:
	UINT m_shaderId{ 0 };
	UINT m_projectionLocation{ 0 };
	UINT m_lookatLocation{ 0 };


	UINT m_viewPositionLocation{ 0 };

	float m_fovY{ 45.f };

	glm::vec3 m_eye{ };
	glm::vec3 m_at{ 0.f,0.f,-1.f };
	glm::vec3 m_up{ 0.f, 1.f, 0.f };

	glm::vec3 m_basisX{ 0.f };
	glm::vec3 m_basisY{ 0.f };
	glm::vec3 m_basisZ{ 0.f };


	float m_nearZ{ 0.1f };
	float m_farZ{ 1000.f };

	float m_aspect{ 0.f };

	GLFWwindow* m_window{ nullptr };

public:

	/// <summary>
	/// Camera Update
	/// </summary>
	/// <param name="DeltaTime">Timer's Delta Time</param>
	void Update(float DeltaTime);

	/// <summary>
	/// Camera Render : Deliver to Shader Perspective Matrix, Lookat Matrix
	/// </summary>
	void Render();





};
