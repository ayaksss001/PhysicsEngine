#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

const int gridWidth = 20;
const int gridHeight = 20;
const float spacing = 1.0f;
glm::vec3 vertices[gridWidth][gridHeight];

void drawSpaceMesh()
{
    for (int x = 0; x < gridWidth; x++)
    {
        for (int z = 0 ; z < gridHeight; z++)
        {
            vertices[x][z] = glm::vec3((x - gridWidth / 2) * spacing, 0.0f, (z - gridHeight / 2) * spacing);
        }
    }

    glMatrixMode(GL_MODELVIEW);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINES);
    
    for (int x = 0; x < gridWidth - 1; ++x)
    {
        for (int z = 0; z < gridHeight; ++z)
        {
            glVertex3fv(glm::value_ptr(vertices[x][z]));
            glVertex3fv(glm::value_ptr(vertices[x + 1][z]));
        }
    }

    for (int x = 0; x < gridWidth; ++x)
    {
        for (int z = 0; z < gridHeight - 1; ++z)
        {
            glVertex3fv(glm::value_ptr(vertices[x][z]));
            glVertex3fv(glm::value_ptr(vertices[x][z + 1]));
        }
    }
    glEnd();
}