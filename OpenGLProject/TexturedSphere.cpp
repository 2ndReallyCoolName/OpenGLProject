#include "TexturedSphere.h"
constexpr double pi = 3.14159265358979323846;


TexturedSphere::TexturedSphere(unsigned int m, unsigned int n)
{
	createVertices(m, n);
	createVertices(m, n);
	Init();
}

void TexturedSphere::draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view)
{
	BindTextures();
	useShader();
	getShader()->setMat4("trans", transformation);
	getShader()->setMat4("view", view);
	getShader()->setMat4("projection", projection);

	GLCall(glBindVertexArray(VAO));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
}

void TexturedSphere::createVertices()
{
	createVertices(20, 20); // default values
}

void TexturedSphere::createVertices(unsigned int m, unsigned int n)
{
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