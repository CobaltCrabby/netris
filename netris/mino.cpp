#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ctime>
#include <iostream>

#include "mino.h"
#include "enum.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char* pvertexShaderSource = "#version 430 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"layout (location = 2) in vec4 aColor;\n"
"out vec2 TexCoord;\n"
"out vec4 ourColor;\n"
"void main() {\n"
"gl_Position = vec4(aPos, 1.0);\n"
"TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
"ourColor = aColor;\n"
"}\0";

const char* pfragmentShaderSource = "#version 430 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoord;\n"
"in vec4 ourColor;\n"
"uniform sampler2D texture1;\n"
"void main() {\n"
"FragColor = texture(texture1, TexCoord) * ourColor;\n"
"}\0";

Mino::Mino() {
    x = 0;
    y = 0;
    r = 0;
    g = 0;
    b = 0;
    g_x = 0;
    g_y = 0;
}

Mino::Mino(int _x, int _y, enum color _c, int gx, int gy) {
    x = _x;
    y = _y;
    r = 0;
    g = 0;
    b = 0;
    g_x = gx;
    g_y = gy;
    color = _c;

    switch (_c) {
        case red:
            r = 1.0f;
            break;
        case green:
            g = 1.0f;
            break;
        case dark_blue:
            r = 55 / 255.0f; 
            g = 60 / 255.0f;
            b = 250 / 255.0f;
            break;
        case yellow:
            g = 1.0f;
            r = 1.0f;
            break;
        case light_blue:
            g = 180 / 255.0f;
            b = 1.0f;
            break;
        case purple:
            r = 227 / 255.0f;
            g = 0 / 255.0f;
            b = 163 / 255.0f;
            break;
        case orange:
            r = 230 / 255.0f;
            g = 100 / 255.0f;
    }

    drawInit();
}

Mino::~Mino() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}

void Mino::drawInit() {
    //setting the grid positions
    vertices[0] = (-g_x / (2.0f / 0.07f)) + 0.07f * x + 0.07f;
    vertices[1] = (-g_y / (2.0f / 0.07f)) + 0.07f * y + 0.07f;
    vertices[9] = vertices[0];
    vertices[10] = vertices[1] - 0.07f;
    vertices[18] = vertices[0] - 0.07f;
    vertices[19] = vertices[10];
    vertices[27] = vertices[18];
    vertices[28] = vertices[1];

    //setting color
    for (int i = 0; i < 4; i++) {
        vertices[5 + 9 * i] = r;
        vertices[6 + 9 * i] = g;
        vertices[7 + 9 * i] = b;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &pvertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &pfragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    //color
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(sizeof(float) * 5));
    glEnableVertexAttribArray(2);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    //idk
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;

    unsigned char* data = stbi_load("mino.png", &width, &height, &channels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);
}

void Mino::draw() {
    glBindTexture(GL_TEXTURE_2D, texture);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

void Mino::resize(float ratio) {
    vertices[0] = ((-g_x / (2.0f / 0.07f)) + 0.07f * x + 0.07f) / ratio;
    vertices[1] = (-g_y / (2.0f / 0.07f)) + 0.07f * y + 0.07f;
    vertices[9] = vertices[0];
    vertices[10] = vertices[1] - 0.07f;
    vertices[18] = vertices[0] - 0.07f / ratio;
    vertices[19] = vertices[10];
    vertices[27] = vertices[18];
    vertices[28] = vertices[1];

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
}

int Mino::getX() {
    return x;
}

int Mino::getY() {
    return y;
}

void Mino::move(int ax, int ay, float ratio) {
    x += ax;
    y += ay;

    resize(ratio);
}
