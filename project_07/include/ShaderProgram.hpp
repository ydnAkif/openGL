#if !defined(SHADERPROGRAM_HPP)
#define SHADERPROGRAM_HPP

#include <glad/glad.h>
#include <string>
#include <map>

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();

    void attachShader(const char *, unsigned int);

    void link();

    void use();

    void addUniform(const std::string &);

    void setUniform(const std::string &, float);

private:
    std::string getShaderFromFile(const char *);
    std::map<std::string, unsigned int> m_UniformVars;
    unsigned int m_ProgramID;
};

#endif // SHADERPROGRAM_HPP
