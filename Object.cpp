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
	
	glm::mat4 finaltrans = glm::translate(m_position) * m_animationCounter->GetRotateAnimation() * glm::scale(m_scale);
	
	Componentptr parent = m_parent;

	//while (parent != nullptr) {

	//}

	if (not m_isAnimated) {
		finaltrans = glm::yawPitchRoll(m_rotation.y, m_rotation.x, m_rotation.z) * glm::translate(m_position)  * glm::scale(m_scale);
	}

	

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
		head->SetScale(MeshPackage.scale );

		m_model->SetPosition(MeshPackage.position);
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

	if (m_LocationAttrib_lightPosition != 0) {
		glUniform3f(m_LocationAttrib_lightPosition, m_model->GetPosition().x , m_model->GetPosition().y, m_model->GetPosition().z);
	}

	m_model->Render();








}








sphere1::sphere1(const std::shared_ptr<Mesh> mesh, UINT shaderId){

	MeshPKG body{ mesh->GetMesh(),static_cast<GLsizei>(mesh->GetVertexCount()),glm::vec3{5.f,0.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{0.005f,0.005f,0.005f},0,0 };

	CreateComponent(body, shaderId);


}

void sphere1::Render()
{
	Object::Render();
}

void sphere1::Update(float DeltaTime)
{
	GetModelInstance()->Update();
	GetModelInstance()->AddRotation(glm::vec3{ 0.f,1.f*DeltaTime,0.f });
}



sphere2::sphere2(const std::shared_ptr<Mesh> mesh, UINT shaderId) {

	MeshPKG body{ mesh->GetMesh(),static_cast<GLsizei>(mesh->GetVertexCount()),glm::vec3{0.f,5.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{0.03f,0.03f,0.03f},0,0 };

	CreateComponent(body, shaderId);


}

void sphere2::Render()
{
	Object::Render();
}

void sphere2::Update(float DeltaTime)
{
	GetModelInstance()->Update();
	GetModelInstance()->AddRotation(glm::vec3{ 0.f,0.f,1.f * DeltaTime });
}






sphere3::sphere3(const std::shared_ptr<Mesh> mesh, UINT shaderId) {

	MeshPKG body{ mesh->GetMesh(),static_cast<GLsizei>(mesh->GetVertexCount()),glm::vec3{0.f,0.f,5.f},glm::vec3{0.f,0.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{0.01f,0.01f,0.01f},0,0 };

	CreateComponent(body, shaderId);


}

void sphere3::Render()
{
	Object::Render();
}

void sphere3::Update(float DeltaTime)
{
	GetModelInstance()->Update();
	GetModelInstance()->AddRotation(glm::vec3{ 1.f * DeltaTime,0.f,0.f });
}


















lightobject::lightobject(const std::shared_ptr<Mesh> mesh, UINT shaderId)
{
	MeshPKG body{ mesh->GetMesh(),static_cast<GLsizei>(mesh->GetVertexCount()),glm::vec3{10.f,10.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{1.f,1.f,1.f},0,0 };
	CreateComponent(body, shaderId);
	SetLightObject(shaderId);

}

void lightobject::Render(){

	
	glm::vec3 pos = GetBodyPosition();
	glUniform3f(m_LocationAttrib_lightPosition, pos.x, pos.y, pos.z);
	Object::Render();


}

void lightobject::Update(float DeltaTime)
{
	GetModelInstance()->Update();



}

board::board(const std::shared_ptr<Mesh> mesh, UINT shaderId)
{
	MeshPKG body{ mesh->GetMesh(),static_cast<GLsizei>(mesh->GetVertexCount()),glm::vec3{-10.f,-7.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{10.f,0.1f,10.f},0,0 };
	CreateComponent(body, shaderId);
}

void board::Render()
{
}

Horn::Horn(UINT shaderId)
{
	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);


	glGenBuffers(1, &m_buffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);




	vertex v1 = { float3{0.f,5.f,0.f},float4{0.5f,0.5f,0.5f,1.f},float2{0.f,0.f},glm::vec3{0.f,1.f,0.f} };
	vertex v2 = { float3{2.5f,0.f,2.5f},float4{0.5f,0.5f,0.5f,1.f},float2{0.f,0.f},glm::vec3{1.f,0.f,1.f} };
	vertex v3 = { float3{-2.5f,0.f,2.5f},float4{0.5f,0.5f,0.5f,1.f},float2{0.f,0.f},glm::vec3{-1.f,0.f,1.f} };
	vertex v4 = { float3{2.5f,0.f,-2.5f},float4{0.5f,0.5f,0.5f,1.f},float2{0.f,0.f},glm::vec3{1.f,0.f,-1.f} };
	vertex v5 = { float3{-2.5f,0.f,-2.5f},float4{0.5f,0.5f,0.5f,1.f},float2{0.f,0.f},glm::vec3{-1.f,0.f,-1.f} };

	m_vertex.push_back(v1); m_vertex.push_back(v2); m_vertex.push_back(v3);
	m_vertex.push_back(v1); m_vertex.push_back(v4); m_vertex.push_back(v5);
	m_vertex.push_back(v1); m_vertex.push_back(v2); m_vertex.push_back(v4);
	m_vertex.push_back(v1); m_vertex.push_back(v3); m_vertex.push_back(v5);


	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * m_vertex.size(), &(m_vertex[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, color));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));
	glEnableVertexAttribArray(2);

	SetLv(5);

	m_transform_Location = glGetUniformLocation(shaderId, "transform");

}

void Horn::Render(){

	glUniformMatrix4fv(m_transform_Location, 1, GL_FALSE, glm::value_ptr(glm::translate(glm::vec3{-1.f,-7.f,-1.f})));
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_vertex.size());

}

void Horn::SetLv(int level){

	m_vertex.clear();
	Sierpinski(5.f, 0.f, 0.f, 0.f, 5.f, 0.f, 0.f, 0.f, 5.f, 0.f, 0.f, 0.f, level);

	glDeleteBuffers(1,&m_buffer);
	glDeleteVertexArrays(1, &m_vao);


	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);


	glGenBuffers(1, &m_buffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * m_vertex.size(), &(m_vertex[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, color));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));
	glEnableVertexAttribArray(2);




}
#include "Input.h"
void Horn::Update()
{
	if (Input::GetInstance()->GetKey('1') == KEY_STATE::DOWN) {
		SetLv(1);
	}
	if (Input::GetInstance()->GetKey('2') == KEY_STATE::DOWN) {
		SetLv(2);
	}
	if (Input::GetInstance()->GetKey('3') == KEY_STATE::DOWN) {
		SetLv(3);
	}

	if (Input::GetInstance()->GetKey('4') == KEY_STATE::DOWN) {
		SetLv(4);
	}

	if (Input::GetInstance()->GetKey('5') == KEY_STATE::DOWN) {
		SetLv(5);
	}

}

void Horn::Sierpinski(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz, float dx, float dy, float dz, int level)
{
	if (level == 0) {

		float4 color{ 0.5f,0.5f,0.5f,1.f };

		m_vertex.push_back(vertex{ float3{ax,ay,az},color,float2{0.f,0.f},glm::vec3{1.f,1.f,1.f} });
		m_vertex.push_back(vertex{ float3{bx,by,bz},color,float2{0.f,0.f},glm::vec3{1.f,1.f,1.f} });
		m_vertex.push_back(vertex{ float3{cx,cy,cz},color,float2{0.f,0.f},glm::vec3{1.f,1.f,1.f} });

		m_vertex.push_back(vertex{ float3{ax,ay,az},color,float2{0.f,0.f},glm::vec3{0.f,-1.f,0.f} });
		m_vertex.push_back(vertex{ float3{bx,by,bz},color,float2{0.f,0.f},glm::vec3{0.f,-1.f,0.f} });
		m_vertex.push_back(vertex{ float3{dx,dy,dz},color,float2{0.f,0.f},glm::vec3{0.f,-1.f,0.f} });

		m_vertex.push_back(vertex{ float3{ax,ay,az},color,float2{0.f,0.f},glm::vec3{-1.f,0.f,0.f} });
		m_vertex.push_back(vertex{ float3{cx,cy,cz},color,float2{0.f,0.f},glm::vec3{-1.f,0.f,0.f} });
		m_vertex.push_back(vertex{ float3{dx,dy,dz},color,float2{0.f,0.f},glm::vec3{-1.f,0.f,0.f} });

		m_vertex.push_back(vertex{ float3{bx,by,bz},color,float2{0.f,0.f},glm::vec3{0.f,0.f,-1.f} });
		m_vertex.push_back(vertex{ float3{cx,cy,cz},color,float2{0.f,0.f},glm::vec3{0.f,0.f,-1.f} });
		m_vertex.push_back(vertex{ float3{dx,dy,dz},color,float2{0.f,0.f},glm::vec3{0.f,0.f,-1.f} });
		 
	
	}
	else {


		float abx = (ax + bx) / 2;
		float aby = (ay + by) / 2;
		float abz = (az + bz) / 2;
		float acx = (ax + cx) / 2;
		float acy = (ay + cy) / 2;
		float acz = (az + cz) / 2;
		float adx = (ax + dx) / 2;
		float ady = (ay + dy) / 2;
		float adz = (az + dz) / 2;
		float bcx = (bx + cx) / 2;
		float bcy = (by + cy) / 2;
		float bcz = (bz + cz) / 2;
		float bdx = (bx + dx) / 2;
		float bdy = (by + dy) / 2;
		float bdz = (bz + dz) / 2;
		float cdx = (cx + dx) / 2;
		float cdy = (cy + dy) / 2;
		float cdz = (cz + dz) / 2;

		Sierpinski(ax, ay, az, abx, aby, abz, acx, acy, acz, adx, ady, adz, level - 1);
		Sierpinski(abx, aby, abz, bx, by, bz, bcx, bcy, bcz, bdx, bdy, bdz, level - 1);
		Sierpinski(acx, acy, acz, bcx, bcy, bcz, cx, cy, cz, cdx, cdy, cdz, level - 1);
		Sierpinski(adx, ady, adz, bdx, bdy, bdz, cdx, cdy, cdz, dx, dy, dz, level - 1);

		



	}
	

}



snow::snow(const std::shared_ptr<Mesh> mesh, UINT shaderId)
{
	MeshPKG body{ mesh->GetMesh(),static_cast<GLsizei>(mesh->GetVertexCount()),glm::vec3{glm::linearRand(-5.f,-2.f),0.f,glm::linearRand(-3.f,0.f)},glm::vec3{0.f,0.f,0.f},glm::vec3{0.f,0.f,0.f},glm::vec3{0.001f,0.001f,0.001f},0,0};
	CreateComponent(body, shaderId);

	speed = glm::linearRand(-10.f, -1.f);
}

void snow::Update(float DeltaTime)
{


	GetModelInstance()->Move(glm::vec3{ 0.f,speed * DeltaTime,0.f });


	if (GetModelInstance()->GetPosition().y < -7.f) {
		GetModelInstance()->SetPosition(glm::vec3{ glm::linearRand(-5.f,5.f),0.f,glm::linearRand(-5.f,5.f)} );
	}

	GetModelInstance()->Update();

}
