#pragma once
#include <glad/glad.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.hpp"

class Object {
    public:
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        float dirX = 0.0f;
        float dirY = 0.0f;
        float dirZ = 0.0f;
        float darkenStrength = 1.0f;
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
        static std::vector<float> vertices;
        static std::vector<GLuint> indices;
        glm::vec4 objColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        Object(double startingX, double startingY, double startingZ);
        void changeColor();
        void changeShape();
        void setProperties(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color, float darkenStrength);
        void render(Shader &shader);
};
