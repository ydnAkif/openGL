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

    int isLinked;
    char log[512];

    glGetShaderiv(m_ProgramID, GL_LINK_STATUS, &isLinked);

    if (!isLinked)
    {
        glGetProgramInfoLog(m_ProgramID, 512, 0, log);
        std::cout << "Program Linking Error: " << std::endl
                  << log << std::endl;
    }
}

void ShaderProgram::use()
{
    glUseProgram(m_ProgramID);
}

void ShaderProgram::addUniform(const std::string &varName)
{
    m_UniformVars[varName] =  glGetUniformLocation(m_ProgramID, varName.c_str());
}

void ShaderProgram::setUniform(const std::string &varName, float value)
{
    glUniform1f(m_UniformVars[varName], value);
}

void ShaderProgram::attachShader(const char *fileName, unsigned int shaderType)
{
    unsigned int shaderId = glCreateShader(shaderType);

    std::string sourceCode = getShaderFromFile(fileName);

    const char *chSourceCode = &sourceCode[0];

    glShaderSource(shaderId, 1, &chSourceCode, 0);

    glCompileShader(shaderId);

    int isCompiled;
    char log[512];

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);

    if (!isCompiled)
    {
        glGetShaderInfoLog(shaderId, 512, 0, log);
        std::cout << "Shader Type: " << shaderType << std::endl
                  << log << std::endl;
    }

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