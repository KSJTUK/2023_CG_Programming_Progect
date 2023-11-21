#include "pch.h"
#include "Rigidbody.h"


void Model::Render()
{
	m_body->Render();

	for (const auto& component : m_child) {
		component->Render();
	}

}

Component::Component(const std::shared_ptr<Mesh> mesh, UINT shaderId)
{
	m_trans_Location = glGetUniformLocation(shaderId, "transform");

	m_vao = mesh->GetMesh();
	m_vertex_Count = static_cast<GLsizei>(mesh->GetVertexCount());

}




void Component::Render(){

	// calculate transform matrix
	
	glm::mat4 finaltrans = glm::translate(m_position);
	
	Componentptr parent = m_parent;

	//while (parent != nullptr) {

	//}



	glUniformMatrix4fv(m_trans_Location, 1, GL_FALSE, glm::value_ptr(finaltrans));
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_vertex_Count);
}

void Component::Update()
{
}






robot::robot(const std::shared_ptr<Mesh> mesh, UINT shaderId){

	m_body = std::make_shared<Component>(mesh, shaderId);




	std::shared_ptr<Component> child = std::make_shared<Component>(mesh, shaderId);

	child->SetPosition(glm::vec3{ 10.f,0.f,0.f });
	child->GetParent(m_body->shared_from_this());

	m_child.push_back(child);



}

void Object::Render()
{
	m_model->Render();

}
