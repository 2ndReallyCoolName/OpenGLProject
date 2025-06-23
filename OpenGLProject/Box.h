#pragma once
#include "Drawable.h"
#include "Shader.h"
#include "Texture.h"


template<DrawableType X>
class Box : public Drawable<Box<X>> 
{
public:
	Box(unsigned int m, unsigned int n) {
		if (!this->staticInitialized) {
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

	Shader* getShader() { return pShader.get(); }

	DrawableType getType() {
		return X;
	}


private:
	void createVertices(unsigned int m, unsigned int n) override {
		assert(n >= 2 && m >= 2);
		int vertex_size = 3;
		unsigned int end = (n + 1) * (m + 1) * 6;

		vertices.reserve(end * vertex_size);

		this->contructFace(m, n, 0, false, false); // Front face
		this->contructFace(m, n, 1, false, false); // Right face 
		this->contructFace(m, n, 2, false, false); // Back face
		this->contructFace(m, n, 3, false, false); // Left face
		this->contructFace(m, n, 4, false, false); // Top face
		this->contructFace(m, n, 5, false, false); // Bottom face

		indices.reserve(end * 6);

		this->createIndices(0, m, n); // Front face
		this->createIndices((m + 1) * (n + 1), m, n); // Right face
		this->createIndices(2 * (m + 1) * (n + 1), m, n); // Back face
		this->createIndices(3 * (m + 1) * (n + 1), m, n); // Left face
		this->createIndices(4 * (m + 1) * (n + 1), m, n); // Top face
		this->createIndices(5 * (m + 1) * (n + 1), m, n); // Bottom face
	}

	void createNormalVertices(unsigned int m, unsigned int n) override {
		assert(n >= 2 && m >= 2);
		int vertex_size = 6;
		unsigned int end = (n + 1) * (m + 1) * 6;

		vertices.reserve(end * vertex_size);

		this->contructFace(m, n, 0, true, false); // Front face
		this->contructFace(m, n, 1, true, false); // Right face 
		this->contructFace(m, n, 2, true, false); // Back face
		this->contructFace(m, n, 3, true, false); // Left face
		this->contructFace(m, n, 4, true, false); // Top face
		this->contructFace(m, n, 5, true, false); // Bottom face

		indices.reserve(end * 6);

		this->createIndices(0, m, n); // Front face
		this->createIndices((m + 1) * (n + 1), m, n); // Right face
		this->createIndices(2 * (m + 1) * (n + 1), m, n); // Back face
		this->createIndices(3 * (m + 1) * (n + 1), m, n); // Left face
		this->createIndices(4 * (m + 1) * (n + 1), m, n); // Top face
		this->createIndices(5 * (m + 1) * (n + 1), m, n); // Bottom face
	}

	void createTexturedVertices(unsigned int m, unsigned int n) override {
		assert(n >= 2 && m >= 2);
		int vertex_size = 5;
		unsigned int end = (n + 1) * (m + 1) * 6;

		vertices.reserve(end * vertex_size);

		this->contructFace(m, n, 0, false, true); // Front face
		this->contructFace(m, n, 1, false, true); // Right face 
		this->contructFace(m, n, 2, false, true); // Back face
		this->contructFace(m, n, 3, false, true); // Left face
		this->contructFace(m, n, 4, false, true); // Top face
		this->contructFace(m, n, 5, false, true); // Bottom face

		indices.reserve(end * 6);

		this->createIndices(0, m, n); // Front face
		this->createIndices((m + 1) * (n + 1), m, n); // Right face
		this->createIndices(2 * (m + 1) * (n + 1), m, n); // Back face
		this->createIndices(3 * (m + 1) * (n + 1), m, n); // Left face
		this->createIndices(4 * (m + 1) * (n + 1), m, n); // Top face
		this->createIndices(5 * (m + 1) * (n + 1), m, n); // Bottom face
	}

	void createTexturedNormalVertices(unsigned int m, unsigned int n) override {
		assert(n >= 2 && m >= 2);
		int vertex_size = 8;
		unsigned int end = (n + 1) * (m + 1) * 6;

		vertices.reserve(end * vertex_size);

		this->contructFace(m, n, 0, true, true); // Front face
		this->contructFace(m, n, 1, true, true); // Right face 
		this->contructFace(m, n, 2, true, true); // Back face
		this->contructFace(m, n, 3, true, true); // Left face
		this->contructFace(m, n, 4, true, true); // Top face
		this->contructFace(m, n, 5, true, true); // Bottom face

		indices.reserve(end * 6);

		this->createIndices(0, m, n); // Front face
		this->createIndices((m + 1) * (n + 1), m, n); // Right face
		this->createIndices(2 * (m + 1) * (n + 1), m, n); // Back face
		this->createIndices(3 * (m + 1) * (n + 1), m, n); // Left face
		this->createIndices(4 * (m + 1) * (n + 1), m, n); // Top face
		this->createIndices(5 * (m + 1) * (n + 1), m, n); // Bottom face
	}

	void contructFace(unsigned int m, unsigned int n, unsigned int face_index, bool normal, bool texture) {
		float x_div = 1.0f / m, y_div = 1.0f / n;
		float z = 0.5f;

		for (unsigned int j = 0; j <= n; j++)
		{
			float y = j * y_div - 0.5f;
			for (unsigned int i = 0; i <= m; i++)
			{
				float x = i * x_div - 0.5f;

				switch (face_index)
				{
				case 0: // Front face
					// Vertex coordinates
					vertices.push_back(x);
					vertices.push_back(y);
					vertices.push_back(z);

					if (texture) {
						// Texture coordinates
						vertices.push_back(x + 0.5f);
						vertices.push_back(y + 0.5f);
					}

					if (normal) {
						// Normal  coordinates
						vertices.push_back(x);
						vertices.push_back(y);
						vertices.push_back(z);
					}

					break;
				case 1: // Right face
					// Vertex coordinates
					vertices.push_back(z);
					vertices.push_back(y);
					vertices.push_back(-x);

					if (texture) {
						// Texture coordinates
						vertices.push_back(x + 0.5f);
						vertices.push_back(y + 0.5f);
					}

					if (normal) {
						// Normal  coordinates
						vertices.push_back(z);
						vertices.push_back(y);
						vertices.push_back(-x);
					}

					break;
				case 2: // Back face
					// Vertex coordinates
					vertices.push_back(-x);
					vertices.push_back(y);
					vertices.push_back(-z);

					if (texture) {
						// Texture coordinates
						vertices.push_back(x + 0.5f);
						vertices.push_back(y + 0.5f);
					}

					if (normal) {
						// Normal  coordinates
						vertices.push_back(-x);
						vertices.push_back(y);
						vertices.push_back(-z);
					}

					break;
				case 3: // Left face
					// Vertex coordinates
					vertices.push_back(-z);
					vertices.push_back(y);
					vertices.push_back(x);

					if (texture) {
						// Texture coordinates
						vertices.push_back(x + 0.5f);
						vertices.push_back(y + 0.5f);
					}

					if (normal) {
						// Normal  coordinates
						vertices.push_back(-z);
						vertices.push_back(y);
						vertices.push_back(x);
					}

					break;
				case 4: // Top face
					// Vertex coordinates
					vertices.push_back(x);
					vertices.push_back(z);
					vertices.push_back(y);

					if (texture) {
						// Texture coordinates
						vertices.push_back(x + 0.5f);
						vertices.push_back(y + 0.5f);
					}

					if (normal) {
						// Normal  coordinates
						vertices.push_back(x);
						vertices.push_back(z);
						vertices.push_back(y);
					}

					break;
				case 5: // Bottom face
					// Vertex coordinates
					vertices.push_back(x);
					vertices.push_back(z);
					vertices.push_back(y);

					if (texture) {
						// Texture coordinates
						vertices.push_back(x + 0.5f);
						vertices.push_back(y + 0.5f);
					}

					if (normal) {
						// Normal  coordinates
						vertices.push_back(x);
						vertices.push_back(z);
						vertices.push_back(y);
					}

					break;
				default:
					break;
				}
			}
		}
	}

	void createIndices(unsigned int startIndex, unsigned int m, unsigned int n) {
		for (unsigned int i = 0; i < m; i++) {
			for (unsigned int j = 0; j < n; j++) {
				unsigned int factor = (m + 1) * j;
				indices.push_back(startIndex + i + factor);
				indices.push_back(startIndex + i + 1 + factor);
				indices.push_back(startIndex + i + (m + 1) + factor);

				indices.push_back(startIndex + i + 1 + factor);
				indices.push_back(startIndex + i + 2 + m + factor);
				indices.push_back(startIndex + i + (m + 1) + factor);
			}
		}
	}

private:
	std::unique_ptr<Shader> pShader;
	std::vector<Texture> textures;

private:
	using Drawable<Box<X>>::vertices;
	using Drawable<Box<X>>::indices;
	using Drawable<Box<X>>::VAO;
	using Drawable<Box<X>>::EBO;
	using Drawable<Box<X>>::staticInitialized;
};

