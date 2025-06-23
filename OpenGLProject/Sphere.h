#pragma once
#include "Drawable.h"
#include "Shader.h"
#include "Texture.h"

template<DrawableType D>
class Sphere : public Drawable<Sphere<D>>
{
public:
	Sphere(unsigned int m, unsigned int n) {
		switch (D) {
		case DrawableType::BASIC:
			createVertices(m, n);
			break;
		case DrawableType::NORMAL :
			createNormalVertices(m, n);
			break;
		case DrawableType::TEXTURE :
			createTexturedVertices(m, n);
			break;
		case DrawableType::NORMALTEXTURE :
			createTexturedNormalVertices(m, n);
			break;
		default:
			createVertices(m, n);
			break;
		}
		this->Init(D);
	}
	
	void  setShaders(std::string vertexShader, std::string fragmentShader) {
		pShader = std::make_unique<Shader>(vertexShader.c_str(), fragmentShader.c_str());
	}

	unsigned int addTexture(std::string fpath) {
		textures.push_back(Texture(fpath));
		return textures.back().GetTextureID();
	}

	void useShader() {
		pShader->use();
		pShader->setMat4("model", this->model);
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

	DrawableType getType() {
		return D;
	}

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

	void createTexturedVertices(unsigned int m, unsigned int n) override {
		assert(m >= 2 && n >= 1);

		vertices.reserve(5 * ((m + 1) * (n)));

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


				// Texture coordinates
				vertices.push_back(tc_x);
				vertices.push_back((float)j / (n * 1.0f));
			}
		}

		indices.reserve(3 * ((m + 1) * (n)));

		unsigned short end = (m + 1) * (n);

		unsigned short j = 0;

		// TexturedSphere indices
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

	void createTexturedNormalVertices(unsigned int m, unsigned int n) override {
		assert(m >= 2 && n >= 1);

		vertices.reserve(8 * ((m + 1) * (n)));

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


				// Texture coordinates
				vertices.push_back(tc_x);
				vertices.push_back((float)j / (n * 1.0f));

				// Normal coordinates
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}
		}

		indices.reserve(3 * ((m + 1) * (n)));

		unsigned short end = (m + 1) * (n);

		unsigned short j = 0;

		// TexturedSphere indices
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

	
protected:
	std::unique_ptr<Shader> pShader;
	std::vector<Texture> textures;

private:
	using Drawable<Sphere<D>>::vertices;
	using Drawable<Sphere<D>>::indices;
	using Drawable<Sphere<D>>::VAO;
	using Drawable<Sphere<D>>::EBO;
	using Drawable<Sphere<D>>::staticInitialized;
	using Drawable<Sphere<D>>::color;
};

