#include "pch.h"
#include "Renderer.h"
#include "Mesh.h"



Renderer::Renderer(GLFWwindow* window)
{
	m_window = window;

	m_shader = std::make_unique<Shader>();
	m_mainCamera = std::make_unique<Camera>(m_window, m_shader->GetShaderID(), glm::vec3{ 1.f,1.f,1.f }, 0.1f, 1000.f);


	
	std::shared_ptr<Mesh> lightmesh = std::make_shared<Mesh>("cube.obj", float3{ 1.f,1.f,1.f });

	testmesh = std::make_shared<Mesh>("sphere.obj", float3{ 0.9f,0.9f,0.5f });
	// find ... iter 


	std::shared_ptr<sphere1>test = std::make_shared<sphere1>(testmesh, m_shader->GetShaderID());


	std::shared_ptr<lightobject> light = std::make_shared<lightobject>(lightmesh, m_shader->GetShaderID());
	m_objectList.push_back(light);
	m_objectList.push_back(test);
	m_objectList.push_back(std::make_shared<sphere2>(testmesh, m_shader->GetShaderID()));
	m_objectList.push_back(std::make_shared<sphere3>(testmesh, m_shader->GetShaderID()));
	m_objectList.push_back(std::make_shared<board>(lightmesh, m_shader->GetShaderID()));

	
	std::shared_ptr<snow> snow1{ nullptr };

	std::shared_ptr<Mesh> snowmesh = std::make_shared<Mesh>("sphere.obj", float3{ 1.f,1.f,1.f });

	for (auto i = 0; i < 40; ++i) {
		snow1 = std::make_shared<snow>(snowmesh, m_shader->GetShaderID());
		m_objectList.push_back(snow1);
	}

	m_horn = std::make_shared<Horn>(m_shader->GetShaderID());

}




void Renderer::Render()
{
	m_mainCamera->Render();

	m_horn->Render();


	for (const auto& object : m_objectList) {
		object->Render();

	}


}

void Renderer::Update(float DeltaTime)
{
	m_mainCamera->Update(DeltaTime);

	m_horn->Update();
	for (const auto& object : m_objectList) {
		object->Update(DeltaTime);

	}
}
