#pragma once
#include "Sphere.h"

class Light : Sphere<DrawableType::NORMAL>
{
public:
	Light(float r, float g, float b);
	Light();
	void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view) override;
	std::vector<float> GetLightColor() { return color; }
	glm::vec3& GetPosition() { return pointLight.position; }

	void SetPosition(float x, float y, float z) { 
		pointLight.position = glm::vec3(x, y, z); 
		this->setModel(std::move(glm::translate(glm::mat4(1.0f), pointLight.position)));
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

	void setPointLight(PointLight&& _pointLight) {
		pointLight = std::move(_pointLight);
	}

	PointLight* getPointLight() {
		return &pointLight;
	}

private:
	void Initialize();
private:
	PointLight pointLight;
private:
	using Drawable<Sphere<DrawableType::NORMAL>>::vertices;
	using Drawable<Sphere<DrawableType::NORMAL>>::indices;
	using Drawable<Sphere<DrawableType::NORMAL>>::VAO;
	using Drawable<Sphere<DrawableType::NORMAL>>::EBO;
	using Drawable<Sphere<DrawableType::NORMAL>>::staticInitialized;
	using Drawable<Sphere<DrawableType::NORMAL>>::color;
	using Sphere<DrawableType::NORMAL>::pShader;
};

