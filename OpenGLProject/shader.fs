#version 460 core
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform sampler2D texture2;

uniform float mixVal;

void main()
{
   FragColor =  mix(texture(ourTexture, TexCoord), texture(texture2, TexCoord), mixVal);
}