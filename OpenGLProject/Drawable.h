#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"

template <class T>
class Drawable {
public:
	Drawable() = default;
	virtual void Init() = 0;

	unsigned int addTexture(std::string fpath) {
		textures.push_back(Texture(fpath));
		return textures.back().GetTextureID();
	}

	void setModel(glm::mat4&& _model) {
		model = _model;
	}

	void  setShaders(std::string vertexShader, std::string fragmentShader) {
		pShader = std::make_unique<Shader>(vertexShader.c_str(), fragmentShader.c_str());
	}

	void bind() {
		glBindVertexArray(VAO);
	}


	void useShader() {
		pShader->use();
		pShader->setMat4("model", model);
		for(unsigned int i = 0; i < textures.size(); i++)
			pShader->setInt("texture" + std::to_string(i), i);
	}

	void BindTextures() {
		for (unsigned int i = 0; i < textures.size(); i++)
			textures[i].BindTexture(i);
	}

	virtual void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view) = 0;

protected:
	
	virtual void createVertices() = 0;

	Shader* getShader() { return pShader.get(); }

protected:
	glm::mat4 model = glm::mat4(1.0f);
	std::unique_ptr<Shader> pShader;
	std::vector<Texture> textures;

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