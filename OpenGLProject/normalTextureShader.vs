#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 trans;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;

void main()
{
	
	TexCoord = aTexCoord;

	FragPos = vec3(model * trans * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model * trans))) * aNormal;  
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}