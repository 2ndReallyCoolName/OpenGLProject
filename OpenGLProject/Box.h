#pragma once
#include "Drawable.h"


class Box : public Drawable 
{
public:
	Box();
	void Init();
	void draw() override;
	void createVertices() override;
};

