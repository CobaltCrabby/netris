#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "grid.h"
#include "enum.h"

Grid* grid;

void window_size_callback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window);
void nextKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
void window2Render(GLFWwindow* window);

GLFWwindow* window2;
bool window2Up = false;

int main(void) {
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 640, "netris", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    if (window2Up && !window2) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    grid = new Grid(10, 20);

    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetKeyCallback(window, nextKeyPress);

    int frame = 0;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(32.0f / 255.0f, 32.0f / 255.0f, 32.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        grid->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
        keyCallback(window);

        if (window2) window2Render(window2);
        
        frame++;

        if (window2 && glfwWindowShouldClose(window2)) {
            glfwDestroyWindow(window2);
            window2Up = false;
            window2 = nullptr;
        }
    }

    glfwTerminate();
    return 0;
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    glClearColor(32.0f / 255.0f, 32.0f / 255.0f, 32.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    grid->resize(width, height);
    grid->draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

int arr = 0;
int das = 7;
int sds = 0;

int dasFrame = 0;
int downDasFrame = 0;
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
            if (dasFrame == das) {
                dasActive = true;
                dasCharge = false;
                dasFrame = 0;
            }

            if (dasActive && dasFrame == arr) {
                if (arr == 0) while (grid->move(x, 0));
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

int rightBind = GLFW_KEY_RIGHT;
int downBind = GLFW_KEY_DOWN;
int leftBind = GLFW_KEY_LEFT;
int hardDropBind = GLFW_KEY_SPACE;
int ccwBind = GLFW_KEY_A;
int cwBind = GLFW_KEY_S;
int holdBind = GLFW_KEY_D;
int _180Bind = GLFW_KEY_F;

int prevLeft = 0;
int prevRight = 0;
int prevDown = 0;
int prevSpace = 0;
int prevA = 0;
int prevS = 0;
int prevD = 0;
int prevF = 0;

void keyCallback(GLFWwindow* window) {
    int left = glfwGetKey(window, leftBind);
    int right = glfwGetKey(window, rightBind);
    int down = glfwGetKey(window, downBind);
    int space = glfwGetKey(window, hardDropBind);

    int a = glfwGetKey(window, ccwBind);
    int s = glfwGetKey(window, cwBind);
    int d = glfwGetKey(window, holdBind);
    int f = glfwGetKey(window, _180Bind);


    if (space && !prevSpace) {
        grid->hardDrop();
    }

    if (d && !prevD) {
        grid->hold();
    }

    //update das frame
    if (left && prevLeft || right && prevRight) {
        dasFrame++;
    }

    if (down && prevDown) {
        downDasFrame++;
    }

    horizontalInput(left, prevLeft, -1);
    horizontalInput(right, prevRight, 1);

    if (downDasFrame >= sds && down) {
        if (sds == 0) while (grid->move(0, -1));
        grid->move(0, -1);
        downDasFrame = 0;
    }

    if (f && !prevF) {
        grid->rotate(2);
    }

    if (a && !prevA) {
        grid->rotate(-1);
    }

    if (s && !prevS) {
        grid->rotate(1);
    }

    prevLeft = left;
    prevRight = right;
    prevDown = down;
    prevSpace = space;
    prevA = a;
    prevS = s;
    prevD = d;
    prevF = f;
}

bool settingBind = false;

void nextKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (settingBind && action == GLFW_PRESS) {
        //hardDropBind = key;
        settingBind = false;
    }
    else if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        settingBind = true;
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && !window2Up){ 
        window2 = glfwCreateWindow(640, 480, "netris settings", NULL, window);
        window2Up = true;
    }
    std::cout << KeyCodeToString((enum KeyCode) key) << std::endl;
}

void window2Render(GLFWwindow* window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(32.0f / 255.0f, 32.0f / 255.0f, 32.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
}