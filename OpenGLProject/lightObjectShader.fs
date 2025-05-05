#version 460 core
out vec4 FragColor;

uniform vec4 lightColor;
uniform vec4 objectColor;

void main(){
    float ambientStrength = 0.1;
    vec3 result = ambientStrength * vec3(lightColor.x, lightColor.y, lightColor.z);
    FragColor = vec4(objectColor*vec4(result, 1.0f));
}