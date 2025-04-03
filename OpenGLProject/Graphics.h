#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Shader.h"
#include "memory"
#include <vector>
#include <GLFW/glfw3.h>
#include "Box.h"



class Graphics
{
public:
	Graphics() = default;
	Graphics(unsigned int screen_width, unsigned int screen_height);
	void ClearScreen();

public:
	Camera camera;

private:
	unsigned int SCR_WIDTH = 0;
	unsigned int SCR_HEIGHT = 0;
};

