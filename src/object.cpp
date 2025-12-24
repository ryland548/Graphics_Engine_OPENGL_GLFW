#include "../includes/object.hpp"

std::vector<float> Object::vertices = {
    -0.5f, -0.5f, -0.5f, 0.6f,
     0.5f, -0.5f, -0.5f, 0.6f,
     0.5f,  0.5f, -0.5f, 0.85f,
    -0.5f,  0.5f, -0.5f, 0.85f,
    -0.5f, -0.5f,  0.5f, 0.6f,
     0.5f, -0.5f,  0.5f, 0.6f,
     0.5f,  0.5f,  0.5f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f,
};

std::vector<GLuint> Object::indices = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    4, 0, 3, 3, 7, 4,
    1, 5, 6, 6, 2, 1,
    4, 5, 1, 1, 0, 4,
    3, 2, 6, 6, 7, 3
};

Object::Object(double startingX, double startingY, double startingZ) {
    x = startingX;
    y = startingY;
    z = startingZ;
}

void Object::changeColor() {

}

void Object::render(Shader &shader) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, y, z));
    model = glm::rotate(model, glm::radians(dirX), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(dirY), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(dirZ), glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3(scale));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(glGetUniformLocation(shader.ID, "uColor"), 1, glm::value_ptr(objColor));
    glUniform1f(glGetUniformLocation(shader.ID, "darkenStrength"), darkenStrength);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(Object::indices.size()), GL_UNSIGNED_INT, 0);
}

void Object::setProperties(glm::vec3 position, glm::vec3 rotation, glm::vec3 size, glm::vec4 color, float darkStrength) {
    x = position.x;
    y = position.y;
    z = position.z;
    dirX = rotation.x;
    dirY = rotation.x;
    dirZ = rotation.z;
    scale = size;
    objColor = color;
    darkenStrength = darkStrength;
}
