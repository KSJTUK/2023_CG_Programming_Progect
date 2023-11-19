#version 440 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Color;
layout(location = 2) in vec3 in_Normal;


uniform mat4 transform;
uniform mat4 perspective;
uniform mat4 lookat;



out vec3 out_Color;


out vec3 out_Frag_position;
out vec3 out_Normal;


void main()
{

	
	gl_Position = perspective * lookat * transform * vec4(in_Position,1.0);

	out_Frag_position = vec3(transform * vec4(in_Position,1.0));

	out_Color = in_Color;

	out_Normal = in_Normal;

}