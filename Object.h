#pragma once
#include "Mesh.h"



class Component : public std::enable_shared_from_this<Component>{
// Constructor and Destructor Area 
public:

	Component() = default;
	Component(const std::shared_ptr<Mesh> mesh, UINT shaderId);
	Component(const UINT buffer, const GLsizei bufferSize,const UINT shaderId);


// Private Function Area 
private:
	std::shared_ptr<Component> m_parent{ nullptr };

	
	UINT m_vao{};
	GLsizei m_vertex_Count{};


	UINT m_trans_Location{};


	glm::vec3 m_position{};
	glm::vec3 m_rotation{};
	glm::vec3 m_scale{};

// Matrix Area 
private:

	glm::mat4 m_position_Matrix{};
	glm::mat4 m_rotation_Matrix{};
	glm::mat4 m_scale_Matrix{};



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

	void AddHead(UINT Buffer, GLsizei Buffersize,UINT shaderId);
	void AddComponent(UINT Buffer, GLsizei BufferSize,UINT shaderId);

	void SetPosition(glm::vec3 Position) { m_position = Position; };
	void Move(glm::vec3 Movement) { m_position += Movement; };



	void Render();
	void Update();



};


struct _TAG_MESHPACKAGE {
	UINT vao{};
	GLsizei vertexcount{};


	glm::vec3 position{};
	glm::vec3 pivot{};
	glm::vec3 rotation{};
	glm::vec3 scale{};


	UINT index{};
	UINT childrenof{};
};

using MKPG = _TAG_MESHPACKAGE;


struct _TAG_ANIMATION {
	glm::vec3 movement{};
	glm::quat rotation{};
};


using ANIM = _TAG_ANIMATION;

class Object abstract{
public:
	Object();

private:
	std::unique_ptr<Model> m_model{ nullptr };


protected:



	void AddPart(const MKPG& MeshPackage, UINT shaderId);

	bool AddAnimation(std::vector<ANIM> Frames,int index);




public:

	void Render();
	virtual void Update(float DeltaTime) = 0;

	

};




// tests
class robot final: public Object  {
public:
	robot(const std::shared_ptr<Mesh> mesh, UINT shaderId);

	void Render();

	virtual void Update(float DeltaTime);
};

