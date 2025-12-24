#include "../includes/shader.hpp"

std::string getFileContents(std::string filePath) {
    std::ifstream file(filePath);
    std::string fileContents = "";
    std::string line = "";
    if (!file.is_open()) {
        std::cout << "Error Opening File.\n";
        return "";
    }
    while (std::getline(file, line)) {
        fileContents += line + '\n';
    }
    file.close();
    return fileContents;
}

Shader::Shader() {
    std::string vertexShaderString = getFileContents(vertexFilePath);
    std::string fragmentShaderString = getFileContents(fragmentFilePath);

    const char* vertexShaderSource = vertexShaderString.c_str();
    const char* fragmentShaderSource = fragmentShaderString.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate() {
    glUseProgram(ID);
}

void Shader::Delete() {
    glUseProgram(0);
    glDeleteProgram(ID);
}
