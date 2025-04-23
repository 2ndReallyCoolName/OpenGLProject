#pragma once
#include "Sphere.h"


class Light : Sphere
{
public:
	Light(float r, float g, float b);
	Light();
	void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view) override;
	std::vector<float> GetLightColor() { return color; }
	std::vector<float> GetPosition() { return position; }

private:
	void Initialize();
private:

	std::vector<float> position = { 0.0f, 0.0f, 0.0f, 1.0f };
};

