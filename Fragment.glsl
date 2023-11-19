#version 440 core

in vec3 out_Color;


in vec3 out_Frag_position;
in vec3 out_Normal;


out vec4 FragColor;



uniform vec3 objectcolor;
uniform vec3 lightcolor;



vec3 light = {1.0,1.0,1.0};
vec3 light_position = {-10.0,10.0,10.0};
void main()
{
	vec3 ambient = 0.001 * light;	 
	
	
	vec3 normalVector = normalize(out_Normal);
	vec3 lightdir = normalize(light_position - out_Frag_position);


	float diffuseLight = max(dot(normalVector,lightdir),0.0);
	vec3 diffuse = diffuseLight * light;
	
	
	
	
	
	
	vec3 result = (ambient + diffuse) * out_Color;







	FragColor = vec4(result,1.0);
}