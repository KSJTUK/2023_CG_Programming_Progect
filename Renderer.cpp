#include "pch.h"
#include "Renderer.h"
#include "Mesh.h"

Renderer::Renderer(GLFWwindow* window)
{
	m_window = window;

	m_shader = std::make_unique<Shader>();
	m_mainCamera = std::make_unique<Camera>(m_window, m_shader->GetShaderID(), glm::vec3{ 1.f,1.f,1.f }, 0.1f, 1000.f);


	Mesh test{ std::string{"teapot.obj"},float3{0.f,1.f,1.f} };


	temp = test.GetMesh();
	temp_size = test.GetVertexCount();


}

void Renderer::Render()
{


	glUseProgram(m_shader->GetShaderID());
	glPolygonMode(GL_FRONT_AND_BACK, m_renderMode );


	
	m_mainCamera->Render();


	glBindVertexArray(temp);
	glDrawArrays(GL_TRIANGLES, 0, temp_size);



}

void Renderer::Update(float DeltaTime)
{
	m_mainCamera->Update(DeltaTime);
}
