#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>

std::string getFileContents(std::string filePath);

class Shader {
    public:
        GLuint ID;
        std::string vertexFilePath = "./data/vertexFile.txt";
        std::string fragmentFilePath = "./data/fragmentFile.txt";
        Shader();
        void Activate();
        void Delete();
};
