#include "Graphics.h"
#include "stb_image.h"
#include "GLErrorHandling.h"

Graphics::Graphics(unsigned int screen_width, unsigned int screen_height)
	: SCR_HEIGHT(screen_height), SCR_WIDTH(screen_width)
{
    glEnable(GL_DEPTH_TEST);
}

void Graphics::ClearScreen()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

