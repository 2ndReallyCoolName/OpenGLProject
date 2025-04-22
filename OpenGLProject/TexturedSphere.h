#pragma once
#include "Drawable.h"
#include "Shader.h"
#include "Texture.h"


class TexturedSphere : public Drawable<TexturedSphere>
{
public:
	TexturedSphere(unsigned int m, unsigned int n);
	void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view) override;

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

	Shader* getShader() { return pShader.get(); }

protected:
	void createVertices() override;
	void createVertices(unsigned int m, unsigned int n);

private:
	std::unique_ptr<Shader> pShader;
	std::vector<Texture> textures;
};

