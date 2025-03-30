#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Shader.h"
#include "memory"
#include <vector>
#include <GLFW/glfw3.h>

class Graphics
{
public:
	Graphics() = default;
	Graphics(unsigned int screen_width, unsigned int screen_height);
	void Draw();

public:
	Camera camera;
private:
	std::vector<float> vertices;
	unsigned int VBO = 0, VAO = 0;
	unsigned int texture1 = 0;
	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;

	glm::mat4 model;
	glm::mat4 projection;

	std::unique_ptr<Shader> pShader;

};

