#version 330 core
out vec4 FragColor;
uniform vec1 ourColor;
in vec3 vertexColor;
void main()
{
   FragColor = vec4(vertexColor.xy, ourColor, 1.0);
}