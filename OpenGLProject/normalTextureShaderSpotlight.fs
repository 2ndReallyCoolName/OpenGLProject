#version 460 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 viewPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Light light;

void main(){

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize( light.position - FragPos );

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff)/epsilon, 0.0, 1.0);

    vec3 ambient  = attenuation * light.ambient * vec3(texture(material.diffuse, TexCoord));

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 diffuse =  intensity * attenuation * light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));  
    vec3 specular = intensity * attenuation * light.specular * (spec * vec3(texture(material.specular, TexCoord)));  
    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(vec4(result, 1.0f));

}