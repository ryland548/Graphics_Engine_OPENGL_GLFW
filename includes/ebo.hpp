#pragma once
#include <glad/glad.h>
#include <string>
#include <iostream>

class EBO {
    public:
        GLuint ID;
        EBO(std::vector<GLuint> indices);
        void Bind();
        void UnBind();
        void Delete();
};
