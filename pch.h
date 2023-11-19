#pragma once

#include <stdio.h>
#include <Windows.h>

// OpenGL 헤더 파일들 추가
#include <gl/glew.h>
#include <gl/glfw3.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <gl/glm/gtx/vector_angle.hpp>
#include <gl/glm/gtx/euler_angles.hpp>

// STL 헤더 파일들 추가
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <list>

using int32 = __int32;
using int64 = __int64;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

struct _TAG_WINDOWINFO {
	GLFWwindow* window{ };
	int32		x{ };
	int32		y{ };
	int32		width{ };
	int32		height{ };
	std::string windowTitle{ };
};

struct _TAG_FLOAT2 {
	float x{ };
	float y{ };
};

struct _TAG_FLOAT3 {
	float x{ };
	float y{ };
	float z{ };
};

struct _TAG_FLOAT4 {
	float x{ };
	float y{ };
	float z{ };
	float w{ };
};

struct _TAG_VERTEX {
	_TAG_FLOAT3 position{ };
	_TAG_FLOAT4 color{ };
	_TAG_FLOAT2 texture{ };
	glm::vec3	normal{ };
};

using float2 = _TAG_FLOAT2;
using float3 = _TAG_FLOAT3;
using float4 = _TAG_FLOAT4;
using vertex = _TAG_VERTEX;

using WINDOWINFORMATION = _TAG_WINDOWINFO;


extern std::unique_ptr<class Engine> engine;