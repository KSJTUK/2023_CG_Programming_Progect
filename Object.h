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

	bool m_isAnimated = false;

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
	void SetScale(glm::vec3 scale) { m_scale = scale; }
	void SetPivot(glm::vec3 pivot) { m_pivot = pivot; };

	void AddRotation(glm::vec3 angle) { m_rotation += angle; };

	void RegisterAnimation(const KeyFrame& Animation);


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


	void AddRotation(glm::vec3 angle) { m_body->AddRotation(angle); };


	void Render();
	void Update();


	glm::vec3 GetPosition() { return m_position; };

	
};





class Object {
public:
	Object();

private:
	std::unique_ptr<Model> m_model{ nullptr };

	int m_LocationAttrib_lightPosition{};


protected:
	void CreateComponent(const MeshPKG& MeshPackage, UINT shaderId);

	void CreateAnimation(const KeyFrame& Animation, int index);
	

	glm::vec3 GetBodyPosition() { m_model->GetPosition(); };


	void SetLightObject(UINT ShaderId) { m_LocationAttrib_lightPosition = glGetUniformLocation(ShaderId, "lightposition"); };

public:

	void Render();
	virtual void Update(float DeltaTime) = 0;

	Model* GetModelInstance() { return m_model.get(); };

};




// tests
class sphere1 final: public Object  {
public:
	sphere1(const std::shared_ptr<Mesh> mesh, UINT shaderId);

	void Render();

	void Update(float DeltaTime);
};



class sphere2 final : public Object {
public:
	sphere2(const std::shared_ptr<Mesh> mesh, UINT shaderId);

	void Render();

	void Update(float DeltaTime);
};



class sphere3 final : public Object {
public:
	sphere3(const std::shared_ptr<Mesh> mesh, UINT shaderId);

	void Render();

	void Update(float DeltaTime);
};


class lightobject final :public Object {
public:
	lightobject(const std::shared_ptr<Mesh> mesh, UINT shaderId);

	void Render();

	void Update(float DeltaTime);

private:

	int m_LocationAttrib_lightPosition{};

};


class board final : public Object {
public:
	board(const std::shared_ptr<Mesh> mesh, UINT shaderId);

	void Render();

	void Update(float DeltaTime) { GetModelInstance()->Update(); };


	
};





class snow final : public Object {
public:
	snow(const std::shared_ptr<Mesh> mesh, UINT shaderId);


	void Render() {};

	void Update(float DeltaTime);

private:

	float speed{};

};



class Horn{
public:
	Horn(UINT shaderId);


	void Render();
	void SetLv(int level);
	void Update();

private:

	UINT m_vao{};
	UINT m_buffer{};

	std::vector<vertex> m_vertex{};



	glm::vec3 m_position{};


	int m_transform_Location{};


	void Sierpinski(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz, float dx, float dy, float dz, int level);

};

/*
void drawSierpinski(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz, float dx, float dy, float dz, int level) {
	if(level == 0) {
		glBegin(GL_TRIANGLES);
		glVertex3f(ax, ay, az);
		glVertex3f(bx, by, bz);
		glVertex3f(cx, cy, cz);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex3f(ax, ay, az);
		glVertex3f(bx, by, bz);
		glVertex3f(dx, dy, dz);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex3f(ax, ay, az);
		glVertex3f(cx, cy, cz);
		glVertex3f(dx, dy, dz);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex3f(bx, by, bz);
		glVertex3f(cx, cy, cz);
		glVertex3f(dx, dy, dz);
		glEnd();
	} else {
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

		drawSierpinski(ax, ay, az, abx, aby, abz, acx, acy, acz, adx, ady, adz, level - 1);
		drawSierpinski(abx, aby, abz, bx, by, bz, bcx, bcy, bcz, bdx, bdy, bdz, level - 1);
		drawSierpinski(acx, acy, acz, bcx, bcy, bcz, cx, cy, cz, cdx, cdy, cdz, level - 1);
		drawSierpinski(adx, ady, adz, bdx, bdy, bdz, cdx, cdy, cdz, dx, dy, dz, level - 1);
	}
}
*/