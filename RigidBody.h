#pragma once
#include "Mesh.h"



class Component : public std::enable_shared_from_this<Component>{
// Constructor and Destructor Area 
public:

	Component() = default;
	Component(const std::shared_ptr<Mesh> mesh, UINT shaderId);


// Private Function Area 
private:
	std::shared_ptr<Component> m_parent{ nullptr };

	
	UINT m_vao{};
	GLsizei m_vertex_Count{};


	UINT m_trans_Location{};


	glm::vec3 m_position{};


// Matrix Area 
private:

	glm::mat4 m_position_Matri    x{};



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
};

using Componentptr = std::shared_ptr<Component>;



class Model
{
public:
	Model() = default;


protected:
	/// <summary>
	/// This is the top tier "Component."
	/// </summary>
	std::shared_ptr<Component> m_body{ nullptr };

	std::vector<std::shared_ptr<Component>> m_child{};

	glm::vec3 m_position{};

private:


public:


	void Render();


};


class Object abstract{
public:
	Object() = default;
	
protected:
	std::unique_ptr<Model> m_model{ nullptr };

	void Render();




};


// tests

class robot : public Object {
public:
	robot(const std::shared_ptr<Mesh> mesh, UINT shaderId);

	void Render();

};

