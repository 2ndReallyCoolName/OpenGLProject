#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Graphics.h"
#include "Box.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Light.h"

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

	void DrawScene();

public:
	int status = -1;
	bool firstMouse = true;
	float lastX = 0.0f;
	float lastY = 0.0f;

	unsigned int SCR_WIDTH = 800;
	unsigned int SCR_HEIGHT = 600;

private:

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

private:
	GLFWwindow* window;
	Graphics graphics;

	glm::mat4 projection = glm::mat4(1.0f);

private:
	std::vector<std::unique_ptr<class DrawableBase>> objects;
	std::vector<std::unique_ptr<Light>> lights;
	std::vector<PointLight*> pointLights;
	SpotLight spotlight;
	DirectionLight dirLight;
};