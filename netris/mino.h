#pragma once
#include "enum.h"

class Mino {
    unsigned int shaderProgram;
    unsigned int VBO, VAO, EBO, texture;
    int x, y;
    float r, g, b;
    int g_x, g_y;
    enum color color;

    float vertices[36] = {
        //vertex           texture      rgba color
        1.0f, 1.0f, 0.0f,  1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f, //top right
        1.0f, -1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f, //bottom right
        -1.0f, -1.0f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f, //bottom left
        -1.0f, 1.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f //top left
    };

    unsigned int indices[6]{
        0, 1, 2,
        0, 2, 3
    };

    public:
        Mino();
        Mino(int _x, int _y, enum color _c, int gx, int gy);
        ~Mino();
        void drawInit();
        void draw();
        void resize(float ratio);
        int getX();
        int getY();
        void move(int x, int y, float ratio);
};