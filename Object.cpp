#include "pch.h"
#include "Object.h"

Component::Component(const std::shared_ptr<Mesh> mesh, UINT shaderId)
{
	
	m_animationCounter = std::make_unique<AnimationCounter>();

	m_trans_Location = glGetUniformLocation(shaderId, "transform");

	m_vao = mesh->GetMesh();
	m_vertex_Count = static_cast<GLsizei>(mesh->GetVertexCount());

}

Component::Component(const UINT buffer, const GLsizei bufferSize, UINT shaderId) : m_vao(buffer), m_vertex_Count(bufferSize)
{
	m_animationCounter = std::make_unique<AnimationCounter>();
	m_trans_Location = glGetUniformLocation(shaderId, "transform");

}




void Component::Render(){

	// calculate transform matrix
	
	glm::mat4 finaltrans = glm::translate(m_position) * m_animationCounter->GetRotateAnimation() * glm::scale(glm::vec3{1.f,1.f,1.f});
	
	Componentptr parent = m_parent;

	//while (parent != nullptr) {

	//}

	

	glUniformMatrix4fv(m_trans_Location, 1, GL_FALSE, glm::value_ptr(finaltrans * glm::translate(m_pivot)));
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_vertex_Count);
}

void Component::Update(){


	// temporary 0.0 deltatime 
	if (m_isAnimated) {
		m_animationCounter->Update(0.0);
	}
	

}

void Component::RegisterAnimation(const KeyFrame& Animation)
{
	m_animationCounter->RegisterMyFrame(Animation);
	if (!m_isAnimated) {
		m_isAnimated = true;
	}


}




void Model::RegistrationBody(UINT Buffer, GLsizei Buffersize, UINT ShaderId){

	m_body = std::make_shared<Component>(Buffer,Buffersize,ShaderId);


}

void Model::RegistrationBody(std::shared_ptr<Component>& comp)
{
	m_body = comp;
}

void Model::RegistrationChild(UINT Buffer, GLsizei BufferSize, UINT shaderId)
{
	m_child.push_back(std::make_shared<Component>(Buffer, BufferSize, shaderId));

	
	
}

void Model::RegistrationChild(std::shared_ptr<Component>& comp)
{
	m_child.push_back(comp);
}



void Model::RegisterBodyAnimation(const KeyFrame& Animation){
	m_body->RegisterAnimation(Animation);
}

void Model::RegisterChildAnimation(const KeyFrame& Animtion, int index)
{
}

void Model::Render()
{
	m_body->Render();

	for (const auto& component : m_child) {
		component->Render();
	}

}

void Model::Update(){

	m_body->SetPosition(m_position);
	
	m_body->Update();
	
	for (const auto& component : m_child) {
		component->Update();
	}


}






Object::Object(){
	m_model = std::make_unique<Model>();


}

void Object::CreateComponent(const MeshPKG& MeshPackage,UINT ShaderId){

	if (MeshPackage.index == 0) {
		Componentptr head = std::make_shared<Component>(MeshPackage.vao, MeshPackage.vertexcount, ShaderId);
		
		head->SetPivot(glm::vec3{ 1.f,0.f,0.f });


		m_model->RegistrationBody(head);
		
	}



}

void Object::CreateAnimation(const KeyFrame& Animation, int index){
	if (index == 0) {
		m_model->RegisterBodyAnimation(Animation);
	}
	else {
		m_model->RegisterChildAnimation(Animation, index);
	}
}



void Object::Render()
{
	m_model->Render();

}

void Object::Update(float DeltaTime)
{
	m_model->Update();

}







robot::robot(const std::shared_ptr<Mesh> mesh, UINT shaderId){

	MeshPKG body{ mesh->GetMesh(),static_cast<GLsizei>(mesh->GetVertexCount()),glm::vec3{0.f,0.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{1.f,1.f,1.f},0,0 };

	CreateComponent(body, shaderId);


	glm::vec3 a1{ 10.f,0.f,20.f };
	glm::vec3 a2{ 0.f,30.f, 60.f };
	glm::vec3 a3{ 20.f,50.f,10.f };

	KeyFrame k1{ glm::vec3{0.f,0.f,0.f},glm::quat(a1),glm::angle(glm::normalize(a1),glm::normalize(a2)) / 1000.f,0.f };
	KeyFrame k2{ glm::vec3{0.f,0.f,0.f},glm::quat(a2),glm::angle(glm::normalize(a2),glm::normalize(a3)) / 1000.f,0.f };
	KeyFrame k3{ glm::vec3{0.f,0.f,0.f},glm::quat(a3),glm::angle(glm::normalize(a2),glm::normalize(a3)) / 1000.f,0.f };
	
	CreateAnimation(k1, 0);
	CreateAnimation(k2, 0);
	CreateAnimation(k3, 0);
}

void robot::Render()
{
	Object::Render();
}

void robot::Update(float DeltaTime)
{
	Object::Update(DeltaTime);
}