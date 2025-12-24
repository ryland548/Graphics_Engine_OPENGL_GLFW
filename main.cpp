#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>

#include "./includes/shader.hpp"
#include "./includes/vbo.hpp"
#include "./includes/vao.hpp"
#include "./includes/ebo.hpp"
#include "./includes/object.hpp"
#include "./includes/camera.hpp"
#include "./includes/ui.hpp"

#include "./lib/imgui/imgui.h"
#include "./lib/imgui/backends/imgui_impl_glfw.h"
#include "./lib/imgui/backends/imgui_impl_opengl3.h"
#include "./lib/stb_image.h"

int screenWidth = 1200;
int screenHeight = 900;
double lastMouseX = screenWidth / 2;
double lastMouseY = screenHeight / 2;
bool firstMouse = true;
std::vector<float> bgColor = {0.0f, 0.0f, 0.0f, 1.0f};

void errorCallback(int errorCode, const char* description) {
    std::cout << "GLFW Error: " << errorCode << ". "  << description << '\n';
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    screenWidth = width;
    screenHeight = height;
}

void init(GLFWwindow* &window) {
    glfwSetErrorCallback(errorCallback);
    if (!glfwInit()) {
        std::cout << "Could not initialize GLFW\n";
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    window = glfwCreateWindow(screenWidth, screenHeight, "Graphics", NULL, NULL);
    if (!window) {
        std::cout << "Could not create GLFW window\n";
        glfwTerminate();
        exit(1);
    }
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Could not initialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(1);
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
}

void cleanUp(GLFWwindow* window) {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void input(GLFWwindow* window, Camera &camera) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        firstMouse = true;
    }
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        if (firstMouse) {
            lastMouseX = mouseX;
            lastMouseY = mouseY;
            firstMouse = false;
        } else {
            camera.turnCamera(mouseX, mouseY, lastMouseX, lastMouseY);
            lastMouseX = mouseX;
            lastMouseY = mouseY;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.moveLeft();
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.moveRight();
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.moveUp();
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.moveDown();
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.speedUp();
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        camera.speedNormal();
    }
}

int main() {
    GLFWwindow* window = nullptr;
    init(window);
    Shader shader = Shader();
    shader.Activate();
    VAO vao = VAO();
    vao.Bind();
    VBO vbo = VBO(Object::vertices);
    EBO ebo = EBO(Object::indices);
    vao.linkAttrib(vbo, 0, 3, 4 * sizeof(float), (void*)0);
    vao.linkAttrib(vbo, 1, 1, 4 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.UnBind();
    vbo.UnBind();
    ebo.UnBind();
    Object object = Object(5, 0, 0);
    Camera camera = Camera(screenWidth, screenHeight, glm::vec3(0.0f, 0.0f, 5.0f));
    Ui ui = Ui();
    ui.init(window);
    float deltaTime;
    float lastFrame;
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        float fps = 1.0f / deltaTime;
        input(window, camera);
        glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.Activate();
        camera.matrix(0.1f, 100.0f, shader, "camMatrix");
        vao.Bind();
        object.setProperties(ui.position, ui.rotation, ui.scale, ui.color, ui.darkenStrength);
        bgColor = {ui.worldColor[0], ui.worldColor[1], ui.worldColor[2], ui.worldColor[3]};
        object.render(shader);
        ui.beginFrame();
        ui.loadUi(fps);
        ui.render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    ui.deleteUi();
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shader.Delete();
    cleanUp(window);
}

