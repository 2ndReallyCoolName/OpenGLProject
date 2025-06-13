#include "Box.h"


Box::Box()
{
    if (!staticInitialized) {
        createVertices();
        Init();
    }
}


void Box::draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view)

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

void Box::createVertices(unsigned int m, unsigned int n)
{
	assert(n >= 2 && m >= 2);
	float x_div = 1.0f / m, y_div = 1.0f / n;
    int vertex_size = 3;
	unsigned int end = (n + 1) * (m + 1) * 6;

    vertices.reserve(end * vertex_size);

	for (unsigned int j = 0; j <= n; j++)
	{
        float y = j * y_div - 0.5f;

        for (unsigned int k = 0; k < 6; k++)
        {
            float z = 

            for (unsigned int i = 0; i <= m; i++)
            {
                float x = i * x_div - 0.5f;
                
                // Vertex coordinates
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(0.5f); // z coordinate for the back face
            }
        }
	}

}

void Box::createNormalVertices(unsigned int m, unsigned int n)
{
}

void Box::createTexturedVertices(unsigned int m, unsigned int n)
{
}

void Box::createTexturedNormalVertices(unsigned int m, unsigned int n)
{
}

void Box::contructFace(unsigned int m, unsigned int n, unsigned int face_index, bool normal, bool texture)
{
	assert(n >= 2 && m >= 2);
	float x_div = 1.0f / m, y_div = 1.0f / n;
	int vertex_size = 3;
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
					vertices.push_back(x+0.5f);
					vertices.push_back(y+0.5f);
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

void Box::createVertices()
{
	vertices = {

    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // 0, 2, 1,  2, 0, 3
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // 4, 5, 6, 6, 7, 4
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 8, 9, 10, 10, 9, 4
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 11, 12, 2, 12, 11,  13
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  // 10, 14, 5, 5, 4, 10

     -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // 3, 2, 9, 9, 11, 2
    };

    indices = {
        0, 2, 1,  2, 0, 3,  //back
        4, 5, 6, 6, 7 ,4,  //front
        8, 9, 10, 10, 9, 4,  // left
        11, 12, 2, 12, 11, 13, // right
        10, 14, 5, 5, 4, 10, // bottom
        3, 2, 15, 15, 11, 2 // top
    };
}