#pragma once
#include <vector>
#include "DrawableBase.h"
#include "GLErrorHandling.h"
#include "Shader.h"

struct Material {
	float shininess = 32.0f;
	float specular[3] = {0.5f, 0.5f, 0.31f};
	float diffuse[3] = {1.0f, 1.0f, 1.0f};
	float ambient[3] = { 1.0f, 1.5f, 1.31f};
};

template <class T>
class Drawable : public DrawableBase {
public:
	Drawable() = default;

	virtual void Init(DrawableType D) {
		if (!staticInitialized) {

			GLCall(glGenVertexArrays(1, &VAO));
			GLCall(glGenBuffers(1, &VBO));
			GLCall(glGenBuffers(1, &EBO));

			GLCall(glBindVertexArray(VAO));

			GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
			GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW));

			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
			GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW));

			switch (D) {
			case BASIC:
				GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
				GLCall(glEnableVertexAttribArray(0));
				break;
			case NORMAL:
				GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
				GLCall(glEnableVertexAttribArray(0));
				GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
				GLCall(glEnableVertexAttribArray(1));
				break;
			case TEXTURE:
				GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
				GLCall(glEnableVertexAttribArray(0));
				GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
				GLCall(glEnableVertexAttribArray(1));
				break;
			case NORMALTEXTURE:
				GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
				GLCall(glEnableVertexAttribArray(0));
				GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))));
				GLCall(glEnableVertexAttribArray(1));
				GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float))));
				GLCall(glEnableVertexAttribArray(2));
				break;
			default:
				GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
				GLCall(glEnableVertexAttribArray(0));
				break;
			}
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

	void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view) {
		DrawableType D = getType();
		if (D == DrawableType::NORMALTEXTURE || D == DrawableType::TEXTURE) {
			BindTextures();
			useShader();
		}
		else {
			useShader();
			getShader()->setFloat4("objectColor", color);
		}
		getShader()->setMat4("trans", transformation);
		getShader()->setMat4("view", view);
		getShader()->setMat4("projection", projection);
		getShader()->setFloat("material.shininess", material.shininess);
		getShader()->setInt("material.diffuse", 0);
		getShader()->setInt("material.specular", 1);

		GLCall(glBindVertexArray(VAO));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
		GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
	}

	void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view, glm::vec3& lightPos) {
		DrawableType D = getType();
		if (D == DrawableType::NORMALTEXTURE || D == DrawableType::TEXTURE) {
			BindTextures();
			useShader();
		}
		else {
			useShader();
			getShader()->setFloat4("objectColor", color);
		}

		getShader()->setMat4("trans", transformation);
		getShader()->setMat4("view", view);
		getShader()->setMat4("projection", projection);
		getShader()->setFloat("material.shininess", material.shininess);
		getShader()->setInt("material.diffuse", 0);
		getShader()->setInt("material.specular", 1);
		getShader()->setFloat3("light.ambient", 0.2f, 0.2f, 0.2f);
		getShader()->setFloat3("light.diffuse", 0.9f, 0.9f, 0.9f);
		getShader()->setFloat3("light.specular", 1.0f, 1.0f, 1.0f);
		getShader()->setFloat3("light.position", lightPos.x, lightPos.y, lightPos.z);
		getShader()->setFloat3("light.direction", -0.2f, -1.0f, -0.3f);
		getShader()->setFloat("light.constant", 0.01f);
		getShader()->setFloat("light.linear", 0.009f);
		getShader()->setFloat("light.quadratic", 0.0302f);


		GLCall(glBindVertexArray(VAO));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
		GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
	}

	void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view, glm::vec3& dirLightDir, glm::vec3& spotlightPos, glm::vec3& spotlightDir, float cutOffAngle, float outerCutoffAngle) {
		DrawableType D = getType();
		if (D == DrawableType::NORMALTEXTURE || D == DrawableType::TEXTURE) {
			BindTextures();
			useShader();
		}
		else {
			useShader();
			getShader()->setFloat4("objectColor", color);
		}

		getShader()->setMat4("trans", transformation);
		getShader()->setMat4("view", view);
		getShader()->setMat4("projection", projection);
		getShader()->setFloat("material.shininess", material.shininess);
		getShader()->setInt("material.diffuse", 0);
		getShader()->setInt("material.specular", 1);
		
		getShader()->setFloat3("dirlight.ambient", 0.2f, 0.2f, 0.2f);
		getShader()->setFloat3("dirlight.diffuse", 0.9f, 0.9f, 0.9f);
		getShader()->setFloat3("dirlight.specular", 1.0f, 1.0f, 1.0f);
		getShader()->setFloat3("dirlight.direction", dirLightDir.x, dirLightDir.y, dirLightDir.z);

		glm::vec3 pointLightPositions[] = {
			glm::vec3(0.7f,  0.2f,  2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3(0.0f,  0.0f, -3.0f)
		};

		// point light 1
		getShader()->setVec3("pointLights[0].position", pointLightPositions[0]);
		getShader()->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		getShader()->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		getShader()->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		getShader()->setFloat("pointLights[0].constant", 1.0f);
		getShader()->setFloat("pointLights[0].linear", 0.09f);
		getShader()->setFloat("pointLights[0].quadratic", 0.032f);
		// point light 2
		getShader()->setVec3("pointLights[1].position", pointLightPositions[1]);
		getShader()->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		getShader()->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		getShader()->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		getShader()->setFloat("pointLights[1].constant", 1.0f);
		getShader()->setFloat("pointLights[1].linear", 0.09f);
		getShader()->setFloat("pointLights[1].quadratic", 0.032f);
		// point light 3
		getShader()->setVec3("pointLights[2].position", pointLightPositions[2]);
		getShader()->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		getShader()->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		getShader()->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		getShader()->setFloat("pointLights[2].constant", 1.0f);
		getShader()->setFloat("pointLights[2].linear", 0.09f);
		getShader()->setFloat("pointLights[2].quadratic", 0.032f);
		// point light 4
		getShader()->setVec3("pointLights[3].position", pointLightPositions[3]);
		getShader()->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		getShader()->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		getShader()->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		getShader()->setFloat("pointLights[3].constant", 1.0f);
		getShader()->setFloat("pointLights[3].linear", 0.09f);
		getShader()->setFloat("pointLights[3].quadratic", 0.032f);

		getShader()->setVec3("spotLight.position", spotlightPos);
		getShader()->setVec3("spotLight.direction", spotlightDir);
		getShader()->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		getShader()->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		getShader()->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		getShader()->setFloat("spotLight.constant", 1.0f);
		getShader()->setFloat("spotLight.linear", 0.09f);
		getShader()->setFloat("spotLight.quadratic", 0.032f);
		getShader()->setFloat("spotLight.cutOff", glm::cos(glm::radians(cutOffAngle)));
		getShader()->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(outerCutoffAngle)));


		GLCall(glBindVertexArray(VAO));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
		GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
	}

	void SetColor(float r, float g, float b, float a) {
		this->color[0] = r;
		this->color[1] = g;
		this->color[2] = b;
		this->color[3] = a;
	}

	virtual void setViewPos(glm::vec3& viewPos) = 0;

	void setMaterial(Material& mat) {
		material = mat;
	}

protected:

	virtual void createVertices(unsigned int m, unsigned int n) = 0;
	virtual void createNormalVertices(unsigned int m, unsigned int n) = 0;
	virtual void createTexturedVertices(unsigned int m, unsigned int n) = 0;
	virtual void createTexturedNormalVertices(unsigned int m, unsigned int n) = 0;

	virtual DrawableType getType() = 0;
	virtual Shader* getShader() = 0;


protected:
	static unsigned int VBO;
	static unsigned int VAO;
	static unsigned int EBO;


	static std::vector<float> vertices;
	static std::vector<unsigned int> indices;
	static bool staticInitialized;

	std::vector<float> color = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	Material material;
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