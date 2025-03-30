#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Graphics.h"

class App
{
public:
	App(unsigned int screen_width, unsigned int screen_height, std::string title);
	~App();
	int Init();
	void Run();
	void cameraProcessMouse(float xOffset, float yOffset);
	void cameraProcessScroll(float yOffset);
	GLFWwindow* getWindow() { return window; }

private:
	void ProcessInput();
	
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
public:
	int status = -1;
	bool firstMouse = true;
	float lastX = 0.0f;
	float lastY = 0.0f;

private:
	unsigned int SCR_WIDTH = 800;
	unsigned int SCR_HEIGHT = 600;


	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

private:
	GLFWwindow* window;
	Graphics graphics;
};