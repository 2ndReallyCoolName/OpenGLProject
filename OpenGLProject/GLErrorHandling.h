#pragma once
#include <glad/glad.h>
#include <iostream>

#define ASSER(x) if (!(x)) \
{ \
	std::cerr << "Assertion failed: " << #x << ", file " << __FILE__ << ", line " << __LINE__ << std::endl; \
	abort(); \
} \

#define GLCall(x) GLClearError(); \
	x; \
	ASSER(GLCheckError(#x))

static void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

static bool GLCheckError(const char* function) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << ")" << function << std::endl;
		return false;
	}
	return true;
}