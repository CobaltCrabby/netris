#pragma once
#define GLEW_STATIC
#include <GL/glew.h>

class Line {
    GLuint shaderProgram;
    unsigned int VBO, VAO;
    float vertices[6];

    public:
        Line(float x1, float y1, float x2, float y2);
        void draw();
        ~Line();
        void resize(float x1, float y1,  float x2, float y2);
};