#pragma once
#include "Drawable.h"


class Box : public Drawable<Box> 
{
public:
	Box();
	void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view) override;
private:
	void createVertices() override;
	void Init();
};

