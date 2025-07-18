#version 460 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec4 lightColor;
uniform vec4 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main(){
    float ambientStrength = 0.1;
    float specularStrength = 0.5;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize( FragPos - lightPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff*vec3(lightColor.x, lightColor.y, lightColor.z);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength*spec*vec3(lightColor.x, lightColor.y, lightColor.z);

    vec3 ambient = ambientStrength * vec3(lightColor.x, lightColor.y, lightColor.z);
    vec3 result = (ambient + diffuse + specular)*vec3(objectColor.x, objectColor.y, objectColor.z);
    FragColor = vec4(objectColor*vec4(result, 1.0f));
}