#pragma once
#include "App.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

App app(1400, 900, "OpenGL Project");

int main()
{
	GLFWwindow* window = app.getWindow();
	int status = app.status;

	if (status == 0)
	{
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		status = app.Init();
	}

	if (status == 0) {
		app.Run();
	}
    return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (app.firstMouse) {
		app.lastX = (float)xpos;
		app.lastY = (float)ypos;
		app.firstMouse = false;
	}

	float xOffset = (float)xpos - app.lastX;
	float yOffset = app.lastY - (float)ypos;

	if (xpos < 40) {
		xOffset = -20.0f;
	}
	else if (xpos > app.SCR_WIDTH - 40) {
		xOffset = 20.0f;
	}
	else if (ypos < 40) {
		yOffset = 20.0f;
	}
	else if (ypos > app.SCR_HEIGHT - 40) {
		yOffset = -20.0f;
	}

	app.lastX = (float)xpos;
	app.lastY = (float)ypos;

	app.cameraProcessMouse(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	app.cameraProcessScroll((float)yoffset);
}
