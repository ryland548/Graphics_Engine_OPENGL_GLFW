#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../lib/imgui/imgui.h"
#include "../lib/imgui/backends/imgui_impl_glfw.h"
#include "../lib/imgui/backends/imgui_impl_opengl3.h"

class Ui {
    public:
        glm::vec4 worldColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
        float darkenStrength = 1.0f;
        int width = 0;
        void init(GLFWwindow* window);
        void loadUi(float fps);
        void render();
        void deleteUi();
        void beginFrame();
};

