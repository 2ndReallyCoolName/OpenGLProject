#pragma once
#include "Drawable.h"
#include "Shader.h"
#include "Texture.h"


class Sphere : public Drawable<Sphere>
{
public:
	Sphere(unsigned int m, unsigned int n);
	void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view) override;

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

	void SetLightColor(float r, float g, float b) {
		pShader->use();
		pShader->setFloat4("lightColor", r, g, b, 1.0f );
	}

	void SetLightColor(float color[]) {
		pShader->use();
		pShader->setFloat4("lightColor", color[0], color[1], color[2], 1.0f);
	}

protected:
	void Init() override;
	void createVertices() override;
	void createVertices(unsigned int m, unsigned int n);

	
private:
	std::unique_ptr<Shader> pShader;
};

