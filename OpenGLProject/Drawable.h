#pragma once
#include <vector>
#include "DrawableBase.h"
#include "GLErrorHandling.h"

template <class T>
class Drawable : public DrawableBase {
public:
	Drawable() = default;

	virtual unsigned int addTexture(std::string fpath) = 0;

	void setModel(glm::mat4&& _model) {
		model = _model;
	}

	virtual void  setShaders(std::string vertexShader, std::string fragmentShader) = 0;

	void bind() {
		glBindVertexArray(VAO);
	}


	virtual void useShader() = 0;

	virtual void BindTextures() = 0;

	virtual void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view) = 0;

protected:
	
	virtual void createVertices() = 0;

protected:
	static unsigned int VBO;
	static unsigned int VAO;
	static unsigned int EBO;

	static std::vector<float> vertices;
	static std::vector<unsigned int> indices;
	static bool staticInitialized;
};

template<class T>
unsigned int Drawable<T>::VBO = 0;

template<class T>
unsigned int Drawable<T>::VAO = 0;

template<class T>
unsigned int Drawable<T>::EBO = 0;

template<class T>
std::vector<float> Drawable<T>::vertices;

template<class T>
std::vector<unsigned int> Drawable<T>::indices;


template<class T>
bool Drawable<T>::staticInitialized = false;