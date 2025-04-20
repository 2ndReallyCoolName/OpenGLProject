#include "Cylinder.h"
constexpr double pi = 3.14159265358979323846;

unsigned int Cylinder::VAO2 = 0;

Cylinder::Cylinder(unsigned int m, unsigned int n)
{
	createVertices(m, n);
	Init();
}

void Cylinder::draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view)
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

void Cylinder::Init()
{
	if (!staticInitialized) {

		GLCall(glGenVertexArrays(1, &VAO));
		GLCall(glGenBuffers(1, &VBO));
		GLCall(glGenBuffers(1, &EBO));

		GLCall(glBindVertexArray(VAO));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW));

		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW));


		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0));
		GLCall(glEnableVertexAttribArray(0));

		GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));
		GLCall(glEnableVertexAttribArray(1));
	}

	staticInitialized = true;
}

void Cylinder::createVertices()
{
	createVertices(20, 10);
}

void Cylinder::createVertices(unsigned int m, unsigned int n)
{
	assert(n >= 2 && m >= 3);
	float long_div = 2 * pi / m, lat_div = 1.0f/n;
	float theta = 0.0f, tc_x = 0.0f;
	
	unsigned int end = (n + 1) * (m + 1);
	face_vertex_end = end;

	vertices.reserve(end*5 + 10 * (1 + m));

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

			float z = k*lat_div - 0.5;


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
		vertices.push_back(cos(i*long_div));
		vertices.push_back(sin(i*long_div));
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
	indices.reserve(3*(m+1)*n + 6*m);

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
