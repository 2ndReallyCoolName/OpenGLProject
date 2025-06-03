#pragma once
#include "Drawable.h"
#include "Shader.h"
#include "Texture.h"


class TexturedSphere : public Drawable<TexturedSphere>
{
public:
	TexturedSphere(unsigned int m, unsigned int n, bool normal);
	void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view) override;
	void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view, glm::vec3& lightPos) override;

	void  setShaders(std::string vertexShader, std::string fragmentShader) {
		pShader = std::make_unique<Shader>(vertexShader.c_str(), fragmentShader.c_str());
	}

	unsigned int addTexture(std::string fpath) {
		textures.push_back(Texture(fpath));
		return textures.back().GetTextureID();
	}

	void useShader() {
		pShader->use();
		pShader->setMat4("model", model);
		for (unsigned int i = 0; i < textures.size(); i++)
			pShader->setInt("texture" + std::to_string(i), i);
	}

	void BindTextures() {
		for (unsigned int i = 0; i < textures.size(); i++)
			textures[i].BindTexture(i);
	}

	void setViewPos(glm::vec3& viewPos) {
		pShader->use();
		pShader->setFloat3("viewPos", viewPos.x, viewPos.y, viewPos.z);
	}

	void SetLightColor(float color[]) {
		pShader->use();
		pShader->setFloat4("lightColor", color[0], color[1], color[2], 1.0f);
	}

	void SetLightColor(float r, float g, float b) {
		pShader->use();
		pShader->setFloat4("lightColor", r, g, b, 1.0f);
	}

	Shader* getShader() { return pShader.get(); }

protected:
	void Init() override;
	void createVertices() override;
	void createVertices(unsigned int m, unsigned int n);

	void createNormalVertices() override;
	void createNormalVertices(unsigned int m, unsigned int n);

private:
	std::unique_ptr<Shader> pShader;
	std::vector<Texture> textures;
};

