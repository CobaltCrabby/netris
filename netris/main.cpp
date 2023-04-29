#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "grid.h"
#include "enum.h"

Grid* grid;

void window_size_callback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window);

int main(void) {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 640, "netris", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    grid = new Grid(10, 20);

    grid->add(dark_blue, 8, 0);
    grid->add(dark_blue, 9, 0);
    grid->add(dark_blue, 9, 1);
    grid->add(dark_blue, 9, 2);

    grid->add(orange, 9, 3);
    grid->add(orange, 9, 4);
    grid->add(orange, 9, 5);
    grid->add(orange, 8, 5);

    grid->add(green, 5, 0);
    grid->add(green, 6, 0);
    grid->add(green, 6, 1);
    grid->add(green, 7, 1);

    grid->add(purple, 5, 3);
    grid->add(purple, 6, 2);
    grid->add(purple, 6, 3);
    grid->add(purple, 7, 3);


    //t piece
    srand((unsigned) time(NULL));
    //grid->addTetromino(static_cast<piece>((int) rand() % 7));
    grid->addTetromino(T);

    glfwSetWindowSizeCallback(window, window_size_callback);

    int frame = 0;

    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.0f, 70.0f / 255.0f, 90.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        grid->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
        keyCallback(window);
        
        frame++;
    }

    glfwTerminate();
    return 0;
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    glClearColor(0.0f, 70.0f / 255.0f, 90.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    grid->resize(width, height);
    grid->draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

int dasFrame = 0;
bool dasActive = false;
bool dasCharge = false;

void horizontalInput(int input, int prev, int x) {
    bool moved = true;
    if (input) {
        if (!prev) {
            moved = grid->move(x, 0);
            dasActive = false;
            dasCharge = true;
        }
        else {
            if (dasFrame == 11) {
                dasActive = true;
                dasCharge = false;
                dasFrame = 0;
            }

            if (dasActive && dasFrame == 2) {
                moved = grid->move(x, 0);
                dasFrame = 0;
            }
        }
    }
    else if (prev) {
        dasFrame = 0;
        dasActive = false;
        dasCharge = false;
    }

    if (!moved) {
        dasFrame = 0;
        dasActive = false;
    }
}

int prevLeft = 0;
int prevRight = 0;
int prevDown = 0;
int prevSpace = 0;
int prevA = 0;
int prevS = 0;

void keyCallback(GLFWwindow* window) {
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);

    int a = glfwGetKey(window, GLFW_KEY_A);
    int s = glfwGetKey(window, GLFW_KEY_S);

    //update das frame (down needs to be here too)
    if (left && prevLeft || right && prevRight || down && prevDown) {
        dasFrame++;
    }

    horizontalInput(left, prevLeft, -1);
    horizontalInput(right, prevRight, 1);

    if (dasFrame == 2 && down) {
        grid->move(0, -1);
        dasFrame = 0;
    }

    if (a && !prevA) {
        grid->rotate(-1);
    }

    if (s && !prevS) {
        grid->rotate(1);
    }

    if (space && !prevSpace) {
        grid->hardDrop();
    }

    prevLeft = left;
    prevRight = right;
    prevDown = down;
    prevSpace = space;
    prevA = a;
    prevS = s;
}