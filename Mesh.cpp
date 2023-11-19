#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(std::string path, float3 color) {

	std::fstream file(path.c_str());




	if (!file) {
		std::cerr << "MESH ERROR : Failed to open " << path << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cerr << path << " is Sucessfully Opened" << std::endl;
	}



	std::vector<float3> verties{};
	std::vector<float2> textures{};
	std::vector<glm::vec3> normals{};


	std::vector<UINT> vertex_indices{};
	std::vector<UINT> normals_indices{};
	std::vector<UINT> texture_indices{};







	std::string head{};



	while (!file.eof()) {


		head.clear();


		file >> head;


		if (head == "#") {
			std::getline(file, head);
			continue;
		}


		if (head == "v") {
			float3 vertex{};

			file >> vertex.x >> vertex.y >> vertex.z;

			verties.push_back(vertex);


		}


		if (head == "vn") {

			glm::vec3 normal{};
			file >> normal.x >> normal.y >> normal.z;

			normals.push_back(normal);


		}



		if (head == "vt") {
			float2 texture{};

			file >> texture.x >> texture.y;
			textures.push_back(texture);


		}

		if (head._Equal("f")) {
			std::string Line[3]{};

			GLuint VertexIndex[3]{};
			GLuint UVIndec[3]{};
			GLuint NormalIndex[3]{};

			file >> Line[0] >> Line[1] >> Line[2];



			for (auto i = 0; i < 3; ++i) {
				std::istringstream iss(Line[i]);
				std::string token{};
				GLuint Data[3]{};
				int dataindex = 0;
				if (Line[i].find("//") != std::string::npos) {
					// 있으면

					std::getline(iss, token, '/');
					if (!token.empty())
						vertex_indices.push_back(static_cast<UINT>(stoi(token) - 1));


					std::getline(iss, token, '/');
					std::getline(iss, token, '/');

					if (!token.empty())
						normals_indices.push_back(static_cast<UINT>(stoi(token) - 1));
				}
				else {
					//없으면 

					std::getline(iss, token, '/');
					if (!token.empty())
						vertex_indices.push_back(static_cast<UINT>(stoi(token) - 1));


					std::getline(iss, token, '/');
					if (!token.empty())
						texture_indices.push_back(static_cast<UINT>(stoi(token) - 1));


					std::getline(iss, token, '/');
					if (!token.empty())
						normals_indices.push_back(static_cast<UINT>(stoi(token) - 1));



				}
			}



		}








	}



	if (texture_indices.size() != 0) {
		for (auto i = 0; i < vertex_indices.size(); ++i) {
			vertex vert{ verties[vertex_indices[i]],float4{color.x,color.y,color.z,1.f},textures[texture_indices[i]],glm::vec3{normals[normals_indices[i]]} };
			m_vertex.push_back(vert);
		}
	}
	else {
		for (auto i = 0; i < vertex_indices.size(); ++i) {
			vertex vert{ verties[vertex_indices[i]],float4{color.x,color.y,color.z,1.f},float2{0.f,0.f},glm::vec3{normals[normals_indices[i]]}};
			m_vertex.push_back(vert);
		}
	}
	


	m_vertexCount = m_vertex.size();






	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);



	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)* m_vertex.size(), &(m_vertex[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, color));
	glEnableVertexAttribArray(1);







	

}
