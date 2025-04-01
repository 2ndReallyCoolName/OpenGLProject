#include "Graphics.h"
#include "stb_image.h"

Graphics::Graphics(unsigned int screen_width, unsigned int screen_height)
	: SCR_HEIGHT(screen_height), SCR_WIDTH(screen_width)
{
    box.Init();
    box.setShaders("shader.vs", "shader.fs");

    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    projection = glm::perspective(glm::radians(45.0f), (float)screen_width / (float)screen_height, 0.1f, 100.0f);

    box.setModel(std::move(model));
    box.getShader()->setMat4("projection", projection);
    box.addTexture("..\\images\\blue_ice.jpg");

    glEnable(GL_DEPTH_TEST);
}

void Graphics::Draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    box.BindTextures();

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.5f));

    box.useShader();
    box.getShader()->setFloat("mixVal", 0.0f);

    projection = glm::perspective(glm::radians(camera.getFov()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    box.getShader()->setMat4("trans", trans);
    box.getShader()->setMat4("view", camera.GetViewMatrix());
    box.getShader()->setMat4("projection", projection);

    box.draw();
}