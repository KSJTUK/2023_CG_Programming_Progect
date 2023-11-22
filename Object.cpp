#include "pch.h"
#include "Object.h"

Component::Component(const std::shared_ptr<Mesh> mesh, UINT shaderId)
{
	m_trans_Location = glGetUniformLocation(shaderId, "transform");

	m_vao = mesh->GetMesh();
	m_vertex_Count = static_cast<GLsizei>(mesh->GetVertexCount());

}

Component::Component(const UINT buffer, const GLsizei bufferSize, UINT shaderId) : m_vao(buffer), m_vertex_Count(bufferSize)
{
	m_trans_Location = glGetUniformLocation(shaderId, "transform");

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

void Component::Update(){

	if (t >= 1.f) {
		m_frame += 1;
	}




	// 기본적인 사원수 애니매이팅은 이 두 줄의 코드로 진행됨
	// 1. 먼저 현재 키프레임과, 다음 키프레임의 쿼터니언을 가져와, 두 쿼터니언을 t 기준으로 선형 보간한다 
	// 2. 그 결과로 나온 쿼터니언을 회전행렬로 변환하여 렌더링 파트로 전달한다. ( 통상 업데이트 이후, 렌더링이 진행되므로, 바로 이 값을 사용할 것이다 ) 
	glm::quat q = glm::slerp(m_frames[m_frame].rotation, m_frames[m_frame + 1].rotation, t);
	glm::mat4 rotationMatrix = glm::mat4_cast(q);


}




void Model::AddHead(UINT Buffer, GLsizei Buffersize, UINT ShaderId){

	m_body = std::make_shared<Component>(Buffer,Buffersize,ShaderId);


}

void Model::AddComponent(UINT Buffer, GLsizei BufferSize, UINT shaderId)
{
	m_child.push_back(std::make_shared<Component>(Buffer, BufferSize, shaderId));

	
	
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
	
}






Object::Object(){
	m_model = std::make_unique<Model>();


}

void Object::AddPart(const MKPG& MeshPackage,UINT ShaderId){

	if (MeshPackage.index == 0) {
		m_model->AddHead(MeshPackage.vao, MeshPackage.vertexcount, ShaderId);
	}



}



void Object::Render()
{
	m_model->Render();

}







robot::robot(const std::shared_ptr<Mesh> mesh, UINT shaderId){

	MKPG body{ mesh->GetMesh(),static_cast<GLsizei>(mesh->GetVertexCount()),glm::vec3{0.f,0.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{1.f,1.f,1.f},0,0 };

	AddPart(body, shaderId);

}

void robot::Render()
{
	Object::Render();
}

void robot::Update(float DeltaTime)
{
}