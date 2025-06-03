#version 460 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main(){

    vec4 objectColor = texture(ourTexture, TexCoord);
    float ambientStrength = 0.5;
    float specularStrength = 1.5;

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