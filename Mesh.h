#pragma once
class Mesh {
public:

	/// <summary>
	/// 
	/// ## THIS IS REGACY CODE , NOT AVAILABLE NOW ##
	/// </summary>
	/// <param name="path">= Path of .obj file relative from source folder</param>
	Mesh(std::string path) = delete ;


	/// <summary>
	/// This is only available Initialzer 
	/// </summary>
	/// <param name="path">= Path of .obj file relative from source folder </param>
	/// <param name="color">= Color of mesh float3{r,g,b} </param>
	Mesh(std::string path, float3 color);


	Mesh(const Mesh& other);

private:

	std::vector<vertex> m_vertex{};



	size_t m_vertexCount{};

	unsigned int m_vao{};
	unsigned int m_vbo{};




public:

	/// <summary>
	/// Get VAO of this mesh 
	/// </summary>
	/// <returns>Unsigned int : mesh's Vertex Array Object </returns>
	const UINT  GetMesh() { return m_vao; }

	/// <summary>
	/// <para>
	/// Get VertexCount of this mesh
	/// </para>
	/// <para>
	/// to use glDrawArrays parameter 
	/// </para>
	/// </summary>
	/// <returns>size_t : vertex count </returns>
	const size_t  GetVertexCount() { return m_vertexCount; }
};


class FBXMeshObject {
private:
	
	
	std::vector<vertex> m_vertex{};
	UINT m_vertexcount{};



};

