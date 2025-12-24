#pragma once
#include <glad/glad.h>
#include <string>
#include <iostream>
#include "vbo.hpp"

class VAO {
    public:
        GLuint ID;
        VAO();
        void linkAttrib(VBO vbo, GLuint layout, GLuint size, GLsizeiptr stride, void* offset);
        void Bind();
        void UnBind();
        void Delete();
};
