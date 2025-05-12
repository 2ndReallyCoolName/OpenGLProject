#pragma once
#include <vector>
#include "DrawableBase.h"
#include "GLErrorHandling.h"

template <class T>
class Drawable : public DrawableBase {
public:
	Drawable() = default;

	virtual void Init() {
		if (!staticInitialized) {

			GLCall(glGenVertexArrays(1, &VAO));
			GLCall(glGenBuffers(1, &VBO));
			GLCall(glGenBuffers(1, &EBO));

			GLCall(glBindVertexArray(VAO));

			GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
			GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW));

			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
			GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW));


			GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
			GLCall(glEnableVertexAttribArray(0));

			GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
			GLCall(glEnableVertexAttribArray(1));
		}

		staticInitialized = true;
	}

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
	virtual void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view, glm::vec3& lightPos) = 0;

	void SetColor(float r, float g, float b, float a) {
		this->color[0] = r;
		this->color[1] = g;
		this->color[2] = b;
		this->color[3] = a;
	}

	void SetLightColor(float r, float g, float b) {
	}

	void SetLightColor(float color[]) {

	}

	virtual void setViewPos(glm::vec3& viewPos) = 0;

protected:

	virtual void createVertices() = 0;
	virtual void createNormalVertices() = 0;


protected:
	static unsigned int VBO;
	static unsigned int VAO;
	static unsigned int EBO;


	static std::vector<float> vertices;
	static std::vector<unsigned int> indices;
	static bool staticInitialized;

	std::vector<float> color = { 1.0f, 1.0f, 1.0f, 1.0f };
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