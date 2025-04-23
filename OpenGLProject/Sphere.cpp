#include "Sphere.h"
constexpr double pi = 3.14159265358979323846;


Sphere::Sphere(unsigned int m, unsigned int n)
{
	createVertices(m, n);
	Init();
}

void Sphere::draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view)
{
	useShader();
	getShader()->setMat4("trans", transformation);
	getShader()->setMat4("view", view);
	getShader()->setMat4("projection", projection);
	getShader()->setFloat4("objectColor", color);

	GLCall(glBindVertexArray(VAO));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
}

void Sphere::createVertices()
{
	createVertices(20, 20);
}

void Sphere::createVertices(unsigned int m, unsigned int n)
{
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


void Sphere::Init() {
	if (!staticInitialized) {

		GLCall(glGenVertexArrays(1, &VAO));
		GLCall(glGenBuffers(1, &VBO));
		GLCall(glGenBuffers(1, &EBO));

		GLCall(glBindVertexArray(VAO));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW));

		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW));


		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
		GLCall(glEnableVertexAttribArray(0));
	}

	staticInitialized = true;
}