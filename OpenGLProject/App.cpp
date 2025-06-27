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

    //objects.push_back(std::make_unique<Box>());
    //objects.back()->setShaders("shader.vs", "shader.fs");
    //objects.back()->addTexture("..\\images\\blue_ice.jpg");


    objects.push_back(std::make_unique<Box<DrawableType::NORMALTEXTURE>>(10, 10));
    objects.back()->setModel(std::move(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, -2.0)), -1.57f, glm::vec3(1.0f, 0.0f, 0.0f)), 0.5f, glm::vec3(0.0f, 1.0f, 0.0f))));
    objects.back()->setShaders("normalTextureShader.vs", "normalTextureShaderSpotlight.fs");
    objects.back()->addTexture("..\\images\\paper.jpg");

    objects.push_back(std::make_unique<Box<DrawableType::NORMALTEXTURE>>(10, 10));
    objects.back()->setModel(std::move(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 6.0f, -5.0)), -1.57f, glm::vec3(1.0f, 0.0f, 0.0f)), 0.5f, glm::vec3(0.0f, 1.0f, 0.0f))));
    objects.back()->setShaders("normalTextureShader.vs", "normalTextureShaderPointLight.fs");
    objects.back()->addTexture("..\\images\\paper.jpg");

    objects.push_back(std::make_unique<Box<DrawableType::NORMALTEXTURE>>(10, 10));
    objects.back()->setModel(std::move(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, -2.0f, 0.0)), -1.57f, glm::vec3(1.0f, 0.0f, 0.0f)), 0.5f, glm::vec3(0.0f, 1.0f, 0.0f))));
    objects.back()->setShaders("normalTextureShader.vs", "normalTextureShaderDirectionalLight.fs");
    objects.back()->addTexture("..\\images\\container2.png");
    objects.back()->addTexture("..\\images\\container2_specular.png");

    objects.push_back(std::make_unique<Sphere<DrawableType::NORMALTEXTURE>>(35, 22));
    objects.back()->setModel(std::move(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0)), -1.57f, glm::vec3(1.0f, 0.0f, 0.0f)), 0.5f, glm::vec3(0.0f, 1.0f, 0.0f))));
    objects.back()->setShaders("normalTextureShader.vs", "normalTextureShader.fs");
    objects.back()->addTexture("..\\images\\earth.jpg");

    objects.push_back(std::make_unique<Cylinder<DrawableType::NORMALTEXTURE>>(35, 22));
    objects.back()->setModel(std::move(glm::rotate(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 0.0)), 1.57f, glm::vec3(1.0f, 0.0f, 0.0f)), 0.5f, glm::vec3(0.0f, 1.0f, 0.0f))));
    objects.back()->setShaders("normalTextureShader.vs", "normalTextureShaderSpotlight.fs");
    objects.back()->addTexture("..\\images\\wood_planks.jpg");

    //objects.push_back(std::make_unique<Sphere>(35, 22, true));
    //objects.back()->SetColor(1.0f, 0.5f, 0.31f, 1.0f);
    //objects.back()->setModel(std::move(glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(0.3, 0.7, 0.2)), (float)(3.5*pi/2), glm::vec3(1.0f, 0.0f,0.0f))));
    ///*objects.back()->setShaders("lightShader.vs", "lightObjectShader.fs");*/
    //objects.back()->setShaders("normalColorShader.vs", "normalColorShader.fs");


	light = std::make_unique<Light>(1.0f, 1.0f, 1.0f);

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
        for (int i = 0; i < objects.size(); i++)
        {
			objects[i]->setViewPos(graphics.camera.getCameraPos());
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        graphics.camera.processKeyboar(Camera_Movement::BACKWARD, deltaTime);
        for (int i = 0; i < objects.size(); i++)
        {
            objects[i]->setViewPos(graphics.camera.getCameraPos());
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        graphics.camera.processKeyboar(Camera_Movement::LEFT, deltaTime);
        for (int i = 0; i < objects.size(); i++)
        {
            objects[i]->setViewPos(graphics.camera.getCameraPos());
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        graphics.camera.processKeyboar(Camera_Movement::RIGHT, deltaTime);
        for (int i = 0; i < objects.size(); i++)
        {
            objects[i]->setViewPos(graphics.camera.getCameraPos());
        }
	}
	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		graphics.camera.processKeyboar(Camera_Movement::UP, deltaTime);
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->setViewPos(graphics.camera.getCameraPos());
		}
	}
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        graphics.camera.processKeyboar(Camera_Movement::DOWN, deltaTime);
        for (int i = 0; i < objects.size(); i++)
        {
            objects[i]->setViewPos(graphics.camera.getCameraPos());
        }
    }
}

void App::DrawScene()
{
    graphics.ClearScreen();


    glm::mat4 view = graphics.camera.GetViewMatrix();

    projection = glm::perspective(glm::radians(graphics.camera.getFov()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f));

    light->SetPosition(10.0f, 0.0f, 0.0f);

    //glm::vec3 lightPos = light->GetPosition();
    glm::vec3 lightPos = graphics.camera.getCameraPos();
    glm::vec3 lightDir = graphics.camera.getCameraFront();

	light->draw(trans, projection, view);

    for (int i = 0; i < objects.size(); i++)
    {
        trans = glm::mat4(1.0f);

        trans = glm::rotate(trans, 0.8f*(float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 0.5f));

		objects[i]->SetLightColor(&(light->GetLightColor()[0]));
        //objects[i]->draw(trans, projection, view, lightPos);
        objects[i]->draw(trans, projection, view, lightPos, lightDir, 20.0f);
    }
}
