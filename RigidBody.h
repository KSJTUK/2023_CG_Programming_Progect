#pragma once
#include "Mesh.h"

class Component {
private:
	std::shared_ptr<Component> m_parent{ nullptr };

public:



};




class Rigidbody
{
public:

	Rigidbody(std::shared_ptr<Mesh> mesh) : m_mesh(mesh) {};



	

private:
	/// <summary>
	/// This is the top tier "Component."
	/// </summary>
	std::shared_ptr<Component> m_body{ nullptr };

	std::shared_ptr<Mesh> m_mesh{ nullptr };


public:


	template<typename T,typename... args>
	void InitializeComponents();




};

