#include "../includes/vao.hpp"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

void VAO::Bind() {
    glBindVertexArray(ID);
}

void VAO::linkAttrib(VBO vbo, GLuint layout, GLuint size, GLsizeiptr stride, void* offset) {
    vbo.Bind();
    glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.UnBind();
}

void VAO::UnBind() {
    glBindVertexArray(0);
}

void VAO::Delete() {
    glDeleteVertexArrays(1, &ID);
}
