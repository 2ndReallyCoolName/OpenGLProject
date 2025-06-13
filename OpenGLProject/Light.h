#pragma once
#include "Sphere.h"


class Light : Sphere
{
public:
	Light(float r, float g, float b);
	Light();
	void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view) override;
	std::vector<float> GetLightColor() { return color; }
	glm::vec3& GetPosition() { return position; }
	void SetPosition(float x, float y, float z) { 
		position = glm::vec3(x, y, z); 
	}

	void SetLightColor(float r, float g, float b) {
		pShader->use();
		pShader->setFloat4("lightColor", r, g, b, 1.0f);
	}

	void SetLightColor(float color[]) {
		pShader->use();
		pShader->setFloat4("lightColor", color[0], color[1], color[2], 1.0f);
	}

	void setViewPos(glm::vec3& viewPos) {
		pShader->use();
		pShader->setFloat3("viewPos", viewPos.x, viewPos.y, viewPos.z);
	}

private:
	void Initialize();
private:

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
};

