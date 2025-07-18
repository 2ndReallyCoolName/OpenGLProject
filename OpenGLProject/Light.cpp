#include "Light.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Light::Light(float r, float g, float b)
	: Sphere<DrawableType::NORMAL>(30, 30)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;

	Initialize();
}

Light::Light()
	: Sphere< DrawableType::NORMAL>(30, 30)
{
	Initialize();
}


void Light::draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view)
{

	//position = transformation * glm::vec4(position, 1.0f);
	this->useShader();

	this->getShader()->setMat4("trans", transformation);
	this->getShader()->setMat4("view", view);
	this->getShader()->setMat4("projection", projection);
	this->getShader()->setMat4("model", this->model);
	this->getShader()->setFloat4("lightColor", color);

	GLCall(glBindVertexArray(VAO));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
}

void Light::Initialize() {
	this->setModel(std::move(glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f)), glm::vec3(0.0, 0.7, 0.0))));
	this->setShaders("lightShader.vs", "lightShader.fs");
	this->getShader()->setFloat4("lightColor", color);
}