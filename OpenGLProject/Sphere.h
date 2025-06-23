#pragma once
#include "Drawable.h"
#include "Shader.h"
#include "Texture.h"

template<DrawableType D>
class Sphere : public Drawable<Sphere<D>>
{
public:
	Sphere(unsigned int m, unsigned int n) {
		createNormalVertices(m, n);
		this->Init(D);
	}

	void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view) override {
		useShader();
		getShader()->setMat4("trans", transformation);
		getShader()->setMat4("view", view);
		getShader()->setMat4("projection", projection);
		getShader()->setFloat4("objectColor", color);

		GLCall(glBindVertexArray(VAO));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
		GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
	}

	void draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view, glm::vec3& lightPos) override {
		useShader();
		getShader()->setFloat3("lightPos", lightPos.x, lightPos.y, lightPos.z);
		getShader()->setMat4("trans", transformation);
		getShader()->setMat4("view", view);
		getShader()->setMat4("projection", projection);
		getShader()->setFloat4("objectColor", color);

		GLCall(glBindVertexArray(VAO));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
		GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
	}
	
	void  setShaders(std::string vertexShader, std::string fragmentShader) {
		pShader = std::make_unique<Shader>(vertexShader.c_str(), fragmentShader.c_str());
	}

	unsigned int addTexture(std::string fpath) { return -1;  }

	void useShader() {
		pShader->use();
		pShader->setMat4("model", this->model);
	}

	void BindTextures() {}

	Shader* getShader() { return pShader.get(); }


protected:
	void createVertices(unsigned int m, unsigned int n) {
		assert(m >= 2 && n >= 1);

		vertices.reserve(3 * ((m + 1) * (n)));

		float theta = 0.0f, phi = 0.0f;

		float m_dv = 2 * pi / m, n_div = pi / n;
		float tc_x = 0.0f;

		for (int j = 0; j <= n; j++)
		{
			phi = j * n_div;
			for (int i = 0; i <= m; i++)
			{
				tc_x = (float)i / (m * 1.0f);
				theta = i * m_dv;
				float x = cos(theta) * sin(phi);
				float y = sin(theta) * sin(phi);

				if (i == m) {
					theta = (i - 1) * m_dv;
					x = cos(0) * sin(phi);
					y = sin(0) * sin(phi);
					tc_x = 1.0f;
				}

				float z = cos(phi);


				// Vertex coordinates
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);

			}
		}

		indices.reserve(3 * ((m + 1) * (n)));

		unsigned short end = (m + 1) * (n);

		unsigned short j = 0;

		// Sphere indices
		for (unsigned short iLong = 0; iLong < end; iLong++) {
			if (iLong != 0 && iLong % (m + 1) == 0) {
				j += 1;
			}

			unsigned short factor = (m + 1) * j;

			indices.push_back(iLong);
			indices.push_back(((iLong + 1) % (m + 1)) + factor);
			indices.push_back(iLong + (m + 1));

			indices.push_back(((iLong + 1) % (m + 1)) + factor);
			indices.push_back((((iLong + 1) % (m + 1)) + factor) + (m + 1));
			indices.push_back(iLong + (m + 1));
		}
	}

	void createNormalVertices(unsigned int m, unsigned int n) {
		assert(m >= 2 && n >= 1);

		vertices.reserve(6 * ((m + 1) * (n)));

		float theta = 0.0f, phi = 0.0f;

		float m_dv = 2 * pi / m, n_div = pi / n;
		float tc_x = 0.0f;

		for (int j = 0; j <= n; j++)
		{
			phi = j * n_div;
			for (int i = 0; i <= m; i++)
			{
				tc_x = (float)i / (m * 1.0f);
				theta = i * m_dv;
				float x = cos(theta) * sin(phi);
				float y = sin(theta) * sin(phi);

				if (i == m) {
					theta = (i - 1) * m_dv;
					x = cos(0) * sin(phi);
					y = sin(0) * sin(phi);
					tc_x = 1.0f;
				}

				float z = cos(phi);


				// Vertex coordinates
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);

				// Normal coordinates
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);

			}
		}

		indices.reserve(3 * ((m + 1) * (n)));

		unsigned short end = (m + 1) * (n);

		unsigned short j = 0;

		// Sphere indices
		for (unsigned short iLong = 0; iLong < end; iLong++) {
			if (iLong != 0 && iLong % (m + 1) == 0) {
				j += 1;
			}

			unsigned short factor = (m + 1) * j;

			indices.push_back(iLong);
			indices.push_back(((iLong + 1) % (m + 1)) + factor);
			indices.push_back(iLong + (m + 1));

			indices.push_back(((iLong + 1) % (m + 1)) + factor);
			indices.push_back((((iLong + 1) % (m + 1)) + factor) + (m + 1));
			indices.push_back(iLong + (m + 1));
		}
	}

	void createTexturedVertices(unsigned int m, unsigned int n) override {}
	void createTexturedNormalVertices(unsigned int m, unsigned int n) override {}

	
protected:
	std::unique_ptr<Shader> pShader;

private:
	using Drawable<Sphere<D>>::vertices;
	using Drawable<Sphere<D>>::indices;
	using Drawable<Sphere<D>>::VAO;
	using Drawable<Sphere<D>>::EBO;
	using Drawable<Sphere<D>>::staticInitialized;
	using Drawable<Sphere<D>>::color;
};

