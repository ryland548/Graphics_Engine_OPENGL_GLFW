#include "../includes/camera.hpp"

Camera::Camera(int screenWidth, int screenHeight, glm::vec3 position) {
    width = screenWidth;
    height = screenHeight;
    pos = position;
}

void Camera::matrix(float nearPlane, float farPlane, Shader& shader, const char* uniform) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(pos, pos + orientation, up);
    projection = glm::perspective(glm::radians(fovdeg), static_cast<float>(width) / static_cast<float>(height), nearPlane, farPlane);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::moveRight() {
    pos += speed * glm::normalize(glm::cross(orientation, up));
}

void Camera::moveLeft() {
    pos += speed * -glm::normalize(glm::cross(orientation, up));
}

void Camera::moveUp() {
    pos += speed * orientation;
}

void Camera::moveDown() {
    pos += speed * -orientation;
}

void Camera::turnCamera(double mouseX, double mouseY, double lastMouseX, double lastMouseY) {
    float xOffset = mouseX - lastMouseX;
    float yOffset = lastMouseY - mouseY;

    xOffset *= sensitivity;
    yOffset *= sensitivity;
    if (abs(xOffset) < 0.01f) xOffset = 0;
    if (abs(yOffset) < 0.01f) yOffset = 0;

    yaw += xOffset;
    pitch += yOffset;

    orientation.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    orientation.y = sin(glm::radians(pitch));
    orientation.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    orientation = glm::normalize(orientation);
    std::cout << "YAW: " << yaw << '\n';
    std::cout << "PITCH: " << pitch << '\n';
}

void Camera::speedUp() {
    speed = fastSpeed;
}

void Camera::speedNormal() {
    speed = normalSpeed;
}

