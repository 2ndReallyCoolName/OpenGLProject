#include "Sphere.h"
constexpr double pi = 3.14159265358979323846;


Sphere::Sphere(unsigned int m, unsigned int n)
{
	createVertices(m, n);
	Init();
}

void Sphere::draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view)
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

void Sphere::createVertices()
{
	createVertices(20, 20); // default values
}

void Sphere::createVertices(unsigned int m, unsigned int n)
{
	assert(m >= 2 && n >= 1);

	float u_tip[] = {0.0f, 1.0f, 0.0f, 0.5f, 0.0f}; // top tip
	const float l_tip[] = { 0.0f, -1.0f, 0.0f, 0.5f, 1.0f }; // bottom tip
	const float long_angle = 2 * pi / m, lat_angle = 2 * pi / n;

	vertices.reserve(5 * (m * n + 2));

	float theta = 0.0f, phi = 0.0f;
	
	float m_dv = 2*pi / m, n_div = 2*pi / n;

	for (int i = 0; i < m; i++)
	{
		theta = i * m_dv;
		for (int j = 0; j < n; j++)
		{
			phi = j * n_div;
			float x = cos(theta) * sin(phi);
			float y = sin(theta) * sin(phi);
			float z = cos(phi);

			// Vertex coordinates
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// Texture coordinates
			vertices.push_back(x);
			vertices.push_back(y);
		}
	}

	vertices.insert(vertices.end(), u_tip, u_tip + 5);
	vertices.insert(vertices.end(), l_tip, l_tip + 5);

	const auto ilCenter = (unsigned int)(m * n);
	const auto iuCenter = ilCenter + 1;

	indices.reserve(3 * (m*2 + 2*m * (n -1)));

	unsigned short end = m * (n - 1);
	unsigned short j = 0;

	// l tip indices
	for (unsigned short iLong = 0; iLong < m; iLong++) {
		indices.push_back(ilCenter);
		indices.push_back((iLong + 1) % m);
		indices.push_back(iLong);
	}
	 
	// Sphere indices
	for (unsigned short iLong = 0; iLong < end; iLong++) {
		if (iLong != 0 && iLong % m == 0) {
			j += 1;
		}

		unsigned short factor = m * j;

		indices.push_back(iLong);
		indices.push_back(((iLong + 1) % m) + factor);
		indices.push_back(iLong + m);

		indices.push_back(((iLong + 1) % m) + factor);
		indices.push_back(((iLong + 1) % m) + factor + 1);
		indices.push_back(iLong + m);
	}

	// u tip indices
	for (unsigned short iLong = end; iLong < m+end; iLong++) {
		indices.push_back(iuCenter);
		indices.push_back(iLong);
		indices.push_back((iLong + 1) % m);
	}
	
}
