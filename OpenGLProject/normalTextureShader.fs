#version 460 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

void main(){

    vec4 objectColor = texture(ourTexture, TexCoord);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize( lightPos - FragPos );
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = vec3(lightColor.x, lightColor.y, lightColor.z)*material.diffuse;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular*spec*vec3(lightColor.x, lightColor.y, lightColor.z);

    vec3 ambient = material.ambient * vec3(lightColor.x, lightColor.y, lightColor.z);
    vec3 result = (diff*(ambient + diffuse + specular))*vec3(objectColor.x, objectColor.y, objectColor.z);
    FragColor = vec4(objectColor*vec4(result, 1.0f));
}