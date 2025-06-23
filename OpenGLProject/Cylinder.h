#pragma once
#include "Drawable.h"
#include "Shader.h"
#include "Texture.h"


template<DrawableType X>
class Cylinder : public Drawable<Cylinder<X>>
{
public:
	Cylinder(unsigned int m, unsigned int n) {
		if (!staticInitialized) {
			switch (X) {
			case BASIC:
				createVertices(m, n);
				break;
			case NORMAL:
				createNormalVertices(m, n);
				break;
			case TEXTURE:
				createTexturedVertices(m, n);
				break;
			case NORMALTEXTURE:
				createTexturedNormalVertices(m, n);
				break;
			default:
				createVertices(m, n);
				break;
			}
			this->Init(X);
		}
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

	DrawableType getType() {
		return X;
	}

private:
	void createVertices(unsigned int m, unsigned int n) override {
		assert(n >= 2 && m >= 3);
		short vertex_size = 3;
		float long_div = 2 * pi / m, lat_div = 1.0f / n;
		float theta = 0.0f, tc_x = 0.0f;

		unsigned int end = (n + 1) * (m + 1);
		face_vertex_end = end;

		vertices.reserve(end * vertex_size + 2 * vertex_size * (1 + m));

		for (unsigned int k = 0; k <= n; k++) {

			for (unsigned int i = 0; i <= m; i++) {

				tc_x = (float)i / (m * 1.0f);
				theta = i * long_div;
				float x = cos(theta);
				float y = sin(theta);

				if (i == m) {
					theta = (i - 1) * long_div;
					x = cos(0);
					y = sin(0);
					tc_x = 1.0f;
				}

				float z = k * lat_div - 0.5;


				// Vertex coordinates
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}
		}

		// bottom vertices
		for (unsigned int i = 0; i < m; i++) {
			// vertex coordinates
			vertices.push_back(cos(i * long_div));
			vertices.push_back(sin(i * long_div));
			vertices.push_back(-0.5f);
		}

		// top vertices
		for (unsigned int i = 0; i < m; i++) {
			// vertex coordinates
			vertices.push_back(cos(i * long_div));
			vertices.push_back(sin(i * long_div));
			vertices.push_back(0.5f);
		}

		// Top and bottom center vertices 

		float lc[] = { 0.0f, 0.0f, -0.5f };
		float uc[] = { 0.0f, 0.0f, 0.5f };

		for (float i : lc) { vertices.push_back(i); }
		for (float i : uc) { vertices.push_back(i); }

		// Indices
		indices.reserve(3 * (m + 1) * n + 6 * m);

		unsigned short j = 0;

		std::cout << end << std::endl;

		// Cylinder face indices
		for (unsigned short iLong = 0; iLong < end - m - 1; iLong++) {
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

		face_index_end = end - m - 1;

		unsigned int bci = (vertices.size() / vertex_size) - 2;
		unsigned int uci = (vertices.size() / vertex_size) - 1;

		// Bottom face indices
		for (unsigned int i = 0; i < m; i++) {
			indices.push_back(end + i);
			indices.push_back(bci);

			if (i + 1 < m) {
				indices.push_back(end + i + 1);
			}
			else {
				indices.push_back(end);
			}
		}

		end += m;

		// Top face indices
		for (unsigned int i = 0; i < m; i++) {
			indices.push_back(end + i);
			indices.push_back(uci);

			if (i + 1 < m) {
				indices.push_back(end + i + 1);
			}
			else {
				indices.push_back(end);
			}
		}
	}

	void createNormalVertices(unsigned int m, unsigned int n) override {
		assert(n >= 2 && m >= 3);
		short vertex_size = 6;
		float long_div = 2 * pi / m, lat_div = 1.0f / n;
		float theta = 0.0f, tc_x = 0.0f;

		unsigned int end = (n + 1) * (m + 1);
		face_vertex_end = end;

		vertices.reserve(end * vertex_size + 2 * vertex_size * (1 + m));

		for (unsigned int k = 0; k <= n; k++) {

			for (unsigned int i = 0; i <= m; i++) {

				tc_x = (float)i / (m * 1.0f);
				theta = i * long_div;
				float x = cos(theta);
				float y = sin(theta);

				if (i == m) {
					theta = (i - 1) * long_div;
					x = cos(0);
					y = sin(0);
					tc_x = 1.0f;
				}

				float z = k * lat_div - 0.5;


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

		// bottom vertices
		for (unsigned int i = 0; i < m; i++) {
			float x = cos(i * long_div);
			float y = sin(i * long_div);
			float z = -0.5f;

			// vertex coordinates
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// Normal coordinates
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		}

		// top vertices
		for (unsigned int i = 0; i < m; i++) {
			float x = cos(i * long_div);
			float y = sin(i * long_div);
			float z = 0.5f;

			// vertex coordinates
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// Normal coordinates
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		}

		// Top and bottom center vertices 

		float lc[] = { 0.0f, 0.0f, -0.5f, 0.0f, 0.0f, -0.5f };
		float uc[] = { 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, -0.5f };

		for (float i : lc) { vertices.push_back(i); }
		for (float i : uc) { vertices.push_back(i); }

		// Indices
		indices.reserve(3 * (m + 1) * n + 6 * m);

		unsigned short j = 0;

		std::cout << end << std::endl;

		// Cylinder face indices
		for (unsigned short iLong = 0; iLong < end - m - 1; iLong++) {
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

		face_index_end = end - m - 1;

		unsigned int bci = (vertices.size() / vertex_size) - 2;
		unsigned int uci = (vertices.size() / vertex_size) - 1;

		// Bottom face indices
		for (unsigned int i = 0; i < m; i++) {
			indices.push_back(end + i);
			indices.push_back(bci);

			if (i + 1 < m) {
				indices.push_back(end + i + 1);
			}
			else {
				indices.push_back(end);
			}
		}

		end += m;

		// Top face indices
		for (unsigned int i = 0; i < m; i++) {
			indices.push_back(end + i);
			indices.push_back(uci);

			if (i + 1 < m) {
				indices.push_back(end + i + 1);
			}
			else {
				indices.push_back(end);
			}
		}
	}

	void createTexturedVertices(unsigned int m, unsigned int n) override {
		assert(n >= 2 && m >= 3);
		float long_div = 2 * pi / m, lat_div = 1.0f / n;
		float theta = 0.0f, tc_x = 0.0f;

		unsigned int end = (n + 1) * (m + 1);
		face_vertex_end = end;

		vertices.reserve(end * 5 + 10 * (1 + m));

		for (unsigned int k = 0; k <= n; k++) {

			for (unsigned int i = 0; i <= m; i++) {

				tc_x = (float)i / (m * 1.0f);
				theta = i * long_div;
				float x = cos(theta);
				float y = sin(theta);

				if (i == m) {
					theta = (i - 1) * long_div;
					x = cos(0);
					y = sin(0);
					tc_x = 1.0f;
				}

				float z = k * lat_div - 0.5;


				// Vertex coordinates
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);


				// Texture coordinates
				vertices.push_back(tc_x);
				vertices.push_back((float)(n - k) / (n * 1.0f));
			}
		}

		// bottom vertices
		for (unsigned int i = 0; i < m; i++) {
			// vertex coordinates
			vertices.push_back(cos(i * long_div));
			vertices.push_back(sin(i * long_div));
			vertices.push_back(-0.5f);


			// texture coordinates
			vertices.push_back(cos(i * long_div));
			vertices.push_back(sin(i * long_div));
		}

		// top vertices
		for (unsigned int i = 0; i < m; i++) {
			// vertex coordinates
			vertices.push_back(cos(i * long_div));
			vertices.push_back(sin(i * long_div));
			vertices.push_back(0.5f);


			// texture coordinates
			vertices.push_back(cos(i * long_div));
			vertices.push_back(sin(i * long_div));
		}

		// Top and bottom center vertices 

		float lc[] = { 0.0f, 0.0f, -0.5f, 0.5f, 0.5f };
		float uc[] = { 0.0f, 0.0f, 0.5f, 0.5f, 0.5f };

		for (float i : lc) { vertices.push_back(i); }
		for (float i : uc) { vertices.push_back(i); }

		// Indices
		indices.reserve(3 * (m + 1) * n + 6 * m);

		unsigned short j = 0;

		std::cout << end << std::endl;

		// Cylinder face indices
		for (unsigned short iLong = 0; iLong < end - m - 1; iLong++) {
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

		face_index_end = end - m - 1;

		unsigned int bci = (vertices.size() / 5) - 2;
		unsigned int uci = (vertices.size() / 5) - 1;

		// Bottom face indices
		for (unsigned int i = 0; i < m; i++) {
			indices.push_back(end + i);
			indices.push_back(bci);

			if (i + 1 < m) {
				indices.push_back(end + i + 1);
			}
			else {
				indices.push_back(end);
			}
		}

		end += m;

		// Top face indices
		for (unsigned int i = 0; i < m; i++) {
			indices.push_back(end + i);
			indices.push_back(uci);

			if (i + 1 < m) {
				indices.push_back(end + i + 1);
			}
			else {
				indices.push_back(end);
			}
		}
	}

	void createTexturedNormalVertices(unsigned int m, unsigned int n) override {
		assert(n >= 2 && m >= 3);
		short vertex_size = 8;
		float long_div = 2 * pi / m, lat_div = 1.0f / n;
		float theta = 0.0f, tc_x = 0.0f;

		unsigned int end = (n + 1) * (m + 1);
		face_vertex_end = end;

		vertices.reserve(end * vertex_size + 2 * vertex_size * (1 + m));

		for (unsigned int k = 0; k <= n; k++) {

			for (unsigned int i = 0; i <= m; i++) {

				tc_x = (float)i / (m * 1.0f);
				theta = i * long_div;
				float x = cos(theta);
				float y = sin(theta);

				if (i == m) {
					theta = (i - 1) * long_div;
					x = cos(0);
					y = sin(0);
					tc_x = 1.0f;
				}

				float z = k * lat_div - 0.5;


				// Vertex coordinates
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);


				// Texture coordinates
				vertices.push_back(tc_x);
				vertices.push_back((float)(n - k) / (n * 1.0f));

				// Normal coordinates
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}
		}

		// bottom vertices
		for (unsigned int i = 0; i < m; i++) {
			float x = cos(i * long_div);
			float y = sin(i * long_div);
			float z = -0.5f;

			// vertex coordinates
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// texture coordinates
			vertices.push_back(x);
			vertices.push_back(y);

			// normal coordinates
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		}

		// top vertices
		for (unsigned int i = 0; i < m; i++) {
			float x = cos(i * long_div);
			float y = sin(i * long_div);
			float z = 0.5f;

			// vertex coordinates
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// texture coordinates
			vertices.push_back(x);
			vertices.push_back(y);

			// normal coordinates
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		}

		// Top and bottom center vertices 

		float lc[] = { 0.0f, 0.0f, -0.5f, 0.5f, 0.5f,  0.0f, 0.0f, -0.5f };
		float uc[] = { 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f };

		for (float i : lc) { vertices.push_back(i); }
		for (float i : uc) { vertices.push_back(i); }

		// Indices
		indices.reserve(3 * (m + 1) * n + 6 * m);

		unsigned short j = 0;

		// Cylinder face indices
		for (unsigned short iLong = 0; iLong < end - m - 1; iLong++) {
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

		face_index_end = end - m - 1;

		unsigned int bci = (vertices.size() / vertex_size) - 2;
		unsigned int uci = (vertices.size() / vertex_size) - 1;

		// Bottom face indices
		for (unsigned int i = 0; i < m; i++) {
			indices.push_back(end + i);
			indices.push_back(bci);

			if (i + 1 < m) {
				indices.push_back(end + i + 1);
			}
			else {
				indices.push_back(end);
			}
		}

		end += m;

		// Top face indices
		for (unsigned int i = 0; i < m; i++) {
			indices.push_back(end + i);
			indices.push_back(uci);

			if (i + 1 < m) {
				indices.push_back(end + i + 1);
			}
			else {
				indices.push_back(end);
			}
		}
	}

private:
	std::unique_ptr<Shader> pShader;
	std::vector<Texture> textures;

	static unsigned int VAO2;

private:
	unsigned int face_vertex_end = 0;
	unsigned int face_index_end = 0;

private:
	using Drawable<Cylinder<X>>::vertices;
	using Drawable<Cylinder<X>>::indices;
	using Drawable<Cylinder<X>>::VAO;
	using Drawable<Cylinder<X>>::EBO;
	using Drawable<Cylinder<X>>::staticInitialized;
	using Drawable<Cylinder<X>>::color;
};


template<DrawableType X>
unsigned int Cylinder<X>::VAO2 = 0;
