#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>


class DrawableBase {
	template<class T>
	friend class Drawable;

public:
	glm::mat4 GetModel() const noexcept {
		return model;
	}

	void setModel(glm::mat4&& _model) {
		model = _model;
	}

	virtual void setShaders(std::string vertexShader, std::string fragmentShader) = 0;
	virtual unsigned int addTexture(std::string fpath) = 0;
	virtual void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view) = 0;


protected:
	glm::mat4 model = glm::mat4(1.0f);
};
