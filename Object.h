#pragma once
#include "Mesh.h"
#include "AnimationCounter.h"


class Component : public std::enable_shared_from_this<Component>{
// Constructor and Destructor Area 
public:

	Component() = default;
	Component(const std::shared_ptr<Mesh> mesh, UINT shaderId);
	Component(const UINT buffer, const GLsizei bufferSize,const UINT shaderId);


// Private Variables Area 
private:
	std::shared_ptr<Component> m_parent{ nullptr };
	std::unique_ptr<AnimationCounter> m_animationCounter{ nullptr };
	
	UINT m_vao{};
	GLsizei m_vertex_Count{};


	UINT m_trans_Location{};



	glm::vec3 m_pivot{};


	glm::vec3 m_position{};
	glm::vec3 m_rotation{};
	glm::vec3 m_scale{};



	std::vector<KeyFrame> m_frames{};
	int m_frame = 0;
	float t = 0.f;



// Matrix Area 
private:

	glm::mat4 m_position_Matrix{1.f};
	glm::mat4 m_rotation_Matrix{1.f};
	glm::mat4 m_scale_Matrix{1.f};



// Public Function Area 
public:

	void Render();
	void Update();


	/// <summary>
	/// This is for child component 
	/// </summary>
	/// <param name="parent"> : Caller's parent </param>
	void GetParent(std::shared_ptr<Component> parent) { m_parent = parent; };
	const UINT GetUniformLocation() { return m_trans_Location; };


	


	void SetPosition(glm::vec3 position) { m_position = position; };
	void SetRotation(glm::vec3 rotation) {}
	void SetScale(glm::vec3 scale) {}
	void SetPivot(glm::vec3 pivot) { m_pivot = pivot; };



	void RegisterAnimation(const KeyFrame& Animation) { m_animationCounter->RegisterMyFrame(Animation); }


};

using Componentptr = std::shared_ptr<Component>;



class Model
{
public:
	Model() = default;


private:
	/// <summary>
	/// This is the top tier "Component."
	/// </summary>
	std::shared_ptr<Component> m_body{ nullptr };

	std::vector<std::shared_ptr<Component>> m_child{};

	glm::vec3 m_position{};


public:


	// Component is not ready
	void RegistrationBody(UINT Buffer, GLsizei Buffersize,UINT shaderId);
	// Component is ready
	void RegistrationBody(std::shared_ptr<Component>& comp);


	// Component is not ready
	void RegistrationChild(UINT Buffer, GLsizei BufferSize,UINT shaderId);
	// Component is ready
	void RegistrationChild(std::shared_ptr<Component>& comp);


	void SetPosition(glm::vec3 Position) { m_position = Position; };
	void Move(glm::vec3 Movement) { m_position += Movement; };


	void RegisterBodyAnimation(const KeyFrame& Animation);
	void RegisterChildAnimation(const KeyFrame& Animtion, int index);


	void Render();
	void Update();



};





class Object {
public:
	Object();

private:
	std::unique_ptr<Model> m_model{ nullptr };


protected:
	void CreateComponent(const MeshPKG& MeshPackage, UINT shaderId);

	void CreateAnimation(const KeyFrame& Animation, int index);
	

public:

	void Render();
	void Update(float DeltaTime);

	

};




// tests
class robot final: public Object  {
public:
	robot(const std::shared_ptr<Mesh> mesh, UINT shaderId);

	void Render();

	void Update(float DeltaTime);
};

