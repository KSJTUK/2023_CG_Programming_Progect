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




	// 임시 테스트용 
	// 두 보간 쿼터니언 사이의 term 이 길어질수록 버벅거리는 현상이 있음
	//=> 각 프레임미다 각의 간격이 일정하지 않은데, t는 일정한값 ( deltatime 으로 하더라도 결국 겂은 두 각의 간격에 연동되지 못할 것이다 )
	// 따라서 두 각의 간격을 일정한 수로 나눈 것을 t 의 간격으로 사용해야 할 것이다.
	glm::quat f1 = glm::quat(glm::radians( glm::vec3(30.f, 10.f, 0.f)));
	m_frames.push_back(ANIM{ glm::vec3{0.f,0.f,0.f},f1 });



	glm::quat f2 = glm::quat(glm::radians(glm::vec3(0.f, 80.f, 0.f)));
	m_frames.push_back(ANIM{ glm::vec3{0.f,0.f,0.f},f2 });



	glm::quat f3 = glm::quat(glm::radians(glm::vec3(0.f, 160.f, 30.f)));
	m_frames.push_back(ANIM{ glm::vec3{0.f,0.f,0.f},f3 });
}




void Component::Render(){

	// calculate transform matrix
	
	glm::mat4 finaltrans = glm::translate(m_position) * m_rotation_Matrix * glm::scale(glm::vec3{1.f,1.f,1.f});
	
	Componentptr parent = m_parent;

	//while (parent != nullptr) {

	//}

	

	glUniformMatrix4fv(m_trans_Location, 1, GL_FALSE, glm::value_ptr(finaltrans * glm::translate(m_pivot)));
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_vertex_Count);
}

void Component::Update(){

	if (t >= 1.f) {
		m_frame += 1;
		t = 0.f;
	}
	else {
		t += 0.001f;
	}

	if (m_frame == m_frames.size() - 1) {
		m_frame = 0;
	}



	// 기본적인 사원수 애니매이팅은 이 두 줄의 코드로 진행됨
	// 1. 먼저 현재 키프레임과, 다음 키프레임의 쿼터니언을 가져와, 두 쿼터니언을 t 기준으로 선형 보간한다 
	// 2. 그 결과로 나온 쿼터니언을 회전행렬로 변환하여 렌더링 파트로 전달한다. ( 통상 업데이트 이후, 렌더링이 진행되므로, 바로 이 값을 사용할 것이다 ) 
	glm::quat q = glm::slerp(m_frames[m_frame].rotation, m_frames[m_frame + 1].rotation, t);
	glm::mat4 rotationMatrix = glm::mat4_cast(q);

	m_rotation_Matrix = rotationMatrix;
	

}




void Model::Registration_Body(UINT Buffer, GLsizei Buffersize, UINT ShaderId){

	m_body = std::make_shared<Component>(Buffer,Buffersize,ShaderId);


}

void Model::Registration_Body(std::shared_ptr<Component>& comp)
{
	m_body = comp;
}

void Model::Registration_Child(UINT Buffer, GLsizei BufferSize, UINT shaderId)
{
	m_child.push_back(std::make_shared<Component>(Buffer, BufferSize, shaderId));

	
	
}

void Model::Registration_Child(std::shared_ptr<Component>& comp)
{
	m_child.push_back(comp);
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

void Object::AddPart(const MKPG& MeshPackage,UINT ShaderId){

	if (MeshPackage.index == 0) {
		Componentptr head = std::make_shared<Component>(MeshPackage.vao, MeshPackage.vertexcount, ShaderId);
		
		head->SetPivot(glm::vec3{ 1.f,0.f,0.f });


		m_model->Registration_Body(head);
		
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

	MKPG body{ mesh->GetMesh(),static_cast<GLsizei>(mesh->GetVertexCount()),glm::vec3{0.f,0.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{1.f,1.f,1.f},0,0 };

	AddPart(body, shaderId);

}

void robot::Render()
{
	Object::Render();
}

void robot::Update(float DeltaTime)
{
	Object::Update(DeltaTime);
}