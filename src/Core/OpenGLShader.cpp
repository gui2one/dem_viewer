#include "OpenGLShader.h"
// #include <glad/glad.h>

OpenGLShader::OpenGLShader()
{
}

// OpenGLShader::~OpenGLShader(){
// 	std::cout << "deleting shader \n\n";
// }

void OpenGLShader::loadVertexShaderSource(std::string filePath)
{
        vertexShaderSource = loadShaderFile(filePath);
}
void OpenGLShader::loadFragmentShaderSource(std::string filePath)
{
        fragmentShaderSource = loadShaderFile(filePath);
}

std::string OpenGLShader::getVertexShaderSource()
{
        return vertexShaderSource;
}
std::string OpenGLShader::getFragmentShaderSource()
{
        return fragmentShaderSource;
}

unsigned int OpenGLShader::compileShader(unsigned int type, const std::string &source)
{
        unsigned int id = glCreateShader(type);
        const char *src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);

        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
                int length;
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
                char *message = (char *)alloca(length * sizeof(char));
                glGetShaderInfoLog(id, length, &length, message);
                std::cout << "OpenGLShader compile failure !!!!!\n";
                std::cout << "in " << (type == GL_VERTEX_SHADER ? "vertex shader\n" : "fragment shader\n");
                std::cout << message << "\n";
        }

        return id;
}

unsigned int OpenGLShader::createShader()
{
        m_id = glCreateProgram();
        unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

        glAttachShader(m_id, vs);
        glAttachShader(m_id, fs);

        glLinkProgram(m_id);
        glValidateProgram(m_id);

        glDetachShader(m_id, vs);
        glDetachShader(m_id, fs);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return m_id;
}

void OpenGLShader::useProgram()
{
        glUseProgram(m_id);
}
