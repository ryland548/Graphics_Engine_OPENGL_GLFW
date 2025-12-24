#pragma once
#include <glad/glad.h>
#include <string>
#include <iostream>

class VBO {
    public:
        GLuint ID;
        VBO(std::vector<float> vertices);
        void Bind();
        void UnBind();
        void Delete();
};
