#version 440 core

in vec3 out_Color;
in vec3 out_Frag_position;
in vec3 out_Normal;


out vec4 FragColor;



uniform vec3 objectcolor;
uniform vec3 lightcolor;
uniform vec3 viewPos;


vec3 light = vec3(1.0,1.0,1.0);
vec3 light_position = {5.0,5.0,5.0};


vec3 specular_color = { 1.0,1.0,1.0 };

vec3 ambient = 0.5 * light;	 

int shininess = 128;

void main()
{
	
	
	vec3 normalVector = normalize(out_Normal);
	vec3 lightdir = normalize(light_position - out_Frag_position);


	float diffuseLight = max(dot(normalVector,lightdir),0.0);
	vec3 diffuse = diffuseLight * light;
	
	

	

		
	vec3 viewdir = normalize(viewPos - out_Frag_position);
	vec3 reflectdir = normalize( reflect(-lightdir,normalVector) );
	float specularLight = max(dot(reflectdir,viewdir),0.0);
	specularLight = pow(specularLight,shininess);
	
	vec3 specular = specularLight * light * specular_color ;
	
	
	
	
	vec3 result = ( ambient + diffuse +specular ) * out_Color;
	//vec3 result = (ambient + diffuse ) * out_Color;






	FragColor = vec4(result,1.0);
}