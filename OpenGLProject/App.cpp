#include "App.h"


App::App(unsigned int screen_width, unsigned int screen_height, std::string title)
	: SCR_WIDTH(screen_width), SCR_HEIGHT(screen_height)
{   
	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title.c_str(), NULL, NULL);
	if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        status = -1;
    }
    else {
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, App::framebuffer_size_callback);
		status = 0;
    }
}

App::~App()
{
    glfwTerminate();
}

int App::Init()
{
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	graphics = Graphics(SCR_WIDTH, SCR_HEIGHT);

    objects.push_back(std::make_unique<Box>());
    objects.back()->setShaders("shader.vs", "shader.fs");
    objects.back()->addTexture("..\\images\\blue_ice.jpg");


    objects.push_back(std::make_unique<Box>());
    objects.back()->setModel(std::move(glm::translate(glm::mat4(1.0f), glm::vec3(0.7, 0.1, 0.1))));
    objects.back()->setShaders("shader.vs", "shader.fs");
    objects.back()->addTexture("..\\images\\paper.jpg");

    objects.push_back(std::make_unique<Box>());
    objects.back()->setModel(std::move(glm::translate(glm::mat4(1.0f), glm::vec3(0.1, 0.7, 0.2))));
    objects.back()->setShaders("shader.vs", "shader.fs");
    objects.back()->addTexture("..\\images\\wall.jpg");


	return 0;
}

void App::Run()
{
	while (!glfwWindowShouldClose(window))
	{
        ProcessInput();
		
        DrawScene();
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void App::cameraProcessScroll(float yOffset)
{
	graphics.camera.processScroll(yOffset);
}

void App::cameraProcessMouse(float xOffset, float yOffset)
{
	graphics.camera.processMouse(xOffset, yOffset);
}

void App::ProcessInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        graphics.camera.processKeyboar(Camera_Movement::FORWARD, deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        graphics.camera.processKeyboar(Camera_Movement::BACKWARD, deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        graphics.camera.processKeyboar(Camera_Movement::LEFT, deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        graphics.camera.processKeyboar(Camera_Movement::RIGHT, deltaTime);
    }
}

void App::DrawScene()
{
    graphics.ClearScreen();

    glm::mat4 view = graphics.camera.GetViewMatrix();

    projection = glm::perspective(glm::radians(graphics.camera.getFov()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    for (int i = 0; i < objects.size(); i++)
    {

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.5f));

        objects[i]->draw(trans, projection, view);
    }
}
