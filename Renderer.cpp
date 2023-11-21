#include "pch.h"
#include "Renderer.h"
#include "Mesh.h"

Renderer::Renderer(GLFWwindow* window)
{
	m_window = window;

	m_shader = std::make_unique<Shader>();
	m_mainCamera = std::make_unique<Camera>(m_window, m_shader->GetShaderID(), glm::vec3{ 1.f,1.f,1.f }, 0.1f, 1000.f);



	testmesh = std::make_shared<Mesh>("cube.obj", float3{ 0.9f,0.9f,0.5f });
	// find ... iter 


	std::shared_ptr<robot>test = std::make_shared<robot>(testmesh, m_shader->GetShaderID());

	m_objectList.push_back(test);

}




void Renderer::Render()
{
	m_mainCamera->Render();




	for (const auto& object : m_objectList) {
		object->Render();

	}


}

void Renderer::Update(float DeltaTime)
{
	m_mainCamera->Update(DeltaTime);
}
