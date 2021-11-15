#if !defined(SHADERPROGRAM_HPP)
#define SHADERPROGRAM_HPP

#include <glad/glad.h>
#include <string>

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();

    void attachShader(const char *, unsigned int);

    void link();

    void use();

private:
    std::string getShaderFromFile(const char *);

    unsigned int m_ProgramID;
};

#endif // SHADERPROGRAM_HPP
