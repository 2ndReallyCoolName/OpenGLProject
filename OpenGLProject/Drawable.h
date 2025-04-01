#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture.h"

class Drawable {
public:
	Drawable() = default;
	virtual void Init() = 0;

	Shader* getShader() { return pShader.get(); }

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

protected:
	virtual void draw() = 0;
	virtual void createVertices() = 0;


protected:
	glm::mat4 model = glm::mat4(1.0f);
	std::unique_ptr<Shader> pShader;
	std::vector<Texture> textures;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	unsigned int VBO = 0, VAO = 0;
	unsigned int EBO = 0;
};