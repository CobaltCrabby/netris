#pragma once
class Button {
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

    unsigned int shaderProgram;
    unsigned int VBO, VAO, EBO, texture;
    float x, y;
    float width, height;
    const char* textureName;

    float vertices[36] = {
        //vertex           texture      rgba color
        1.0f, 1.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f, //top right
        1.0f, -1.0f, 0.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f, //bottom right
        -1.0f, -1.0f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f, //bottom left
        -1.0f, 1.0f, 0.0f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f //top left
    };

    unsigned int indices[6]{
        0, 1, 2,
        0, 2, 3
    };

    public:
        Button(float _x, float _y, float _w, float _h, const char* texture);
        ~Button();
        void drawInit();
        void draw();
        bool checkPress(double x, double y, int wx, int wy);
};