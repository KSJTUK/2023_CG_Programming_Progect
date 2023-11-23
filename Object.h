#pragma once
#include "Mesh.h"

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


// 애니매이션에 위치가 이동할 일이 있을까........
struct _TAG_ANIMATION {
	glm::vec3 movement{};
	glm::quat rotation{};
};

using MKPG = _TAG_MESHPACKAGE;
using ANIM = _TAG_ANIMATION;

class Component : public std::enable_shared_from_this<Component>{
// Constructor and Destructor Area 
public:

	Component() = default;
	Component(const std::shared_ptr<Mesh> mesh, UINT shaderId);
	Component(const UINT buffer, const GLsizei bufferSize,const UINT shaderId);


// Private Variables Area 
private:
	std::shared_ptr<Component> m_parent{ nullptr };

	
	UINT m_vao{};
	GLsizei m_vertex_Count{};


	UINT m_trans_Location{};



	glm::vec3 m_pivot{};


	glm::vec3 m_position{};
	glm::vec3 m_rotation{};
	glm::vec3 m_scale{};



	std::vector<ANIM> m_frames{};
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
	void Registration_Body(UINT Buffer, GLsizei Buffersize,UINT shaderId);
	// Component is ready
	void Registration_Body(std::shared_ptr<Component>& comp);


	// Component is not ready
	void Registration_Child(UINT Buffer, GLsizei BufferSize,UINT shaderId);
	// Component is ready
	void Registration_Child(std::shared_ptr<Component>& comp);


	void SetPosition(glm::vec3 Position) { m_position = Position; };
	void Move(glm::vec3 Movement) { m_position += Movement; };



	void Render();
	void Update();



};





class Object{
public:
	Object();

private:
	std::unique_ptr<Model> m_model{ nullptr };


protected:



	void AddPart(const MKPG& MeshPackage, UINT shaderId);

	bool AddAnimation(std::vector<ANIM> Frames,int index);




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

