#include "pch.h"
#include "Shader.h"

#include "pch.h"
#include "Shader.h"

constexpr auto V_ShaderPath = "Vertex.glsl";
constexpr auto F_ShaderPath = "Fragment.glsl";

Shader::Shader() {
	std::ifstream VertexFileptr = std::ifstream(V_ShaderPath, std::ios::in);
	std::ifstream FragmentFileptr = std::ifstream(F_ShaderPath, std::ios::in);

	std::stringstream Vertexstream = std::stringstream{};
	std::stringstream Fragmentstream = std::stringstream{};

	unsigned int vertexShaderID{};
	unsigned int fragmentShaderID{};

	std::string s1{ " " };
	std::string s2{ " " };
	if (VertexFileptr.is_open()) {
		Vertexstream << VertexFileptr.rdbuf();
		s1 = Vertexstream.str();
	}
	else {
		std::cerr << "ERROR : FAILED TO OPEN FILE " << std::endl;
		exit(EXIT_FAILURE);
	}


	if (FragmentFileptr.is_open()) {
		Fragmentstream << FragmentFileptr.rdbuf();
		s2 = Fragmentstream.str();
	}
	else {
		std::cerr << "ERROR : FAILED TO OPEN FILE " << std::endl;
		exit(EXIT_FAILURE);
	}


	const GLchar* VertexShaderSource = s1.c_str();
	const GLchar* FragmentShaderSource = s2.c_str();



	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &VertexShaderSource, NULL);
	glCompileShader(vertexShaderID);

	GLint result{};
	GLchar errorlog[512]{};

	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(vertexShaderID, 512, NULL, errorlog);
		std::cerr << "ERROR : VERTEX SHADER COMPILE ERROR" << std::endl;
		std::cerr << errorlog << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cerr << "VERTEX SHADER SUCESSFULLY COMPILED!" << std::endl;
	}




	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &FragmentShaderSource, NULL);
	glCompileShader(fragmentShaderID);

	ZeroMemory(errorlog, 512);

	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, errorlog);
		std::cerr << "ERROR : FRAGMENT SHADER COMPILE ERROR" << std::endl;
		std::cerr << errorlog << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cerr << "FRAGMENT SHADER SUCESSFULLY COMPILED!" << std::endl;
	}

	m_shaderID = glCreateProgram();
	glAttachShader(m_shaderID, vertexShaderID);
	glAttachShader(m_shaderID, fragmentShaderID);

	glLinkProgram(m_shaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);


	ZeroMemory(errorlog, 512);
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &result);

	if (!result) {
		glGetProgramInfoLog(m_shaderID, 512, NULL, errorlog);
		std::cerr << "ERROR : SHADER LINK FAILED" << std::endl;
		std::cerr << errorlog << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cerr << "SHADERS SUCESSFULLY CREATED" << std::endl;
	}

	glUseProgram(m_shaderID);

}
