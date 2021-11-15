#include <glad/glad.h>

#include "ShaderProgram.hpp"

#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram()
{
    m_ProgramID = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_ProgramID);
}

void ShaderProgram::link()
{
    glLinkProgram(m_ProgramID);
}

void ShaderProgram::use()
{
    glUseProgram(m_ProgramID);
}

void ShaderProgram::attachShader(const char *fileName, unsigned int shaderType)
{
    unsigned int shaderId = glCreateShader(shaderType);

    std::string sourceCode = getShaderFromFile(fileName);

    const char *chSourceCode = &sourceCode[0];

    glShaderSource(shaderId, 1, &chSourceCode, 0);

    glCompileShader(shaderId);

    glAttachShader(m_ProgramID, shaderId);

    glDeleteShader(shaderId);
}

std::string ShaderProgram::getShaderFromFile(const char *fileName)
{
    std::ifstream file(fileName);

    std::string data;

    if (file.is_open())
    {
        char readChar;

        while ((readChar = file.get()) != EOF)
        {
            data += readChar;
        }

        file.close();
    }

    return data;
}