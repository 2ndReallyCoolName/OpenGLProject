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
	void SetPosition(float x, float y, float z) { position = glm::vec3(x, y, z); }

private:
	void Initialize();
private:

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
};

