#pragma once

#include <glad/glad.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "shader.hpp"

class Camera {
    public:
        glm::vec3 pos;
        glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        int width;
        int height;
        float normalSpeed = 0.1f;
        float fastSpeed = 0.2f;
        float speed = normalSpeed;
        float sensitivity = 0.12f;
        float fovdeg = 45.0f;
        float yaw = -90.0f;
        float pitch = 0.0f;
        Camera(int screenWidth, int screenHeight, glm::vec3 position);
        void matrix(float nearPlane, float farPlane, Shader& shader, const char* uniform);
        void moveRight();
        void moveLeft();
        void moveUp();
        void moveDown();
        void turnCamera(double mouseX, double mouseY, double lastMouseX, double lastMouseY);
        void speedUp();
        void speedNormal();
};
