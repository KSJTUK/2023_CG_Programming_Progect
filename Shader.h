#pragma once
class Shader {
private:
	unsigned int m_shaderID{};
public:
	Shader();
	unsigned int GetShaderID() { return m_shaderID; };
};




