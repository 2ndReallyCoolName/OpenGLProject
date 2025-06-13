#pragma once
#include "Drawable.h"
#include "Shader.h"
#include "Texture.h"


class Sphere : public Drawable<Sphere>
{
public:
	Sphere(unsigned int m, unsigned int n, bool normal);
	void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view) override;
	void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view, glm::vec3& lightPos) override;
	
	void  setShaders(std::string vertexShader, std::string fragmentShader) {
		pShader = std::make_unique<Shader>(vertexShader.c_str(), fragmentShader.c_str());
	}

	unsigned int addTexture(std::string fpath) { return -1;  }

	void useShader() {
		pShader->use();
		pShader->setMat4("model", model);
	}

	void BindTextures() {}

	Shader* getShader() { return pShader.get(); }


protected:
	void Init() override;
	void InitBasic();
	void createVertices(unsigned int m, unsigned int n);
	void createNormalVertices(unsigned int m, unsigned int n);
	void createTexturedVertices(unsigned int m, unsigned int n) override {}
	void createTexturedNormalVertices(unsigned int m, unsigned int n) override {}

	
protected:
	std::unique_ptr<Shader> pShader;
};

