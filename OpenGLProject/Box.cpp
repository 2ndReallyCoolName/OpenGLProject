#include "Box.h"

Box::Box()
{
    if (!staticInitialized) {
        createVertices();
        Init();
    }
}

void Box::Init()
{
    if (!staticInitialized) {

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    staticInitialized = true;
}

void Box::draw(glm::mat4& transformation, glm::mat4& projection, glm::mat4& view)

{
    BindTextures();
    useShader();
    getShader()->setMat4("trans", transformation);
    getShader()->setMat4("view", view);
    getShader()->setMat4("projection", projection);

	glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
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