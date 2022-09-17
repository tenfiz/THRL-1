#include "ShaderProgram.h"

namespace Renderer {
    ShaderProgram::ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader){
        GLuint vertexShaderID;
        if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)) {
            std::cerr << "VERTEX SHADER: compile-time error" << std::endl;
            return;
        }

        GLuint fragmentShaderID;
        if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {
            std::cerr << "FRAGMENT: compile-time error" << std::endl;
            glDeleteShader(vertexShaderID);
            return;
        }

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertexShaderID);
        glAttachShader(m_ID, fragmentShaderID);
        glLinkProgram(m_ID);

        GLint programLinkStatus;
        glGetProgramiv(m_ID, GL_LINK_STATUS, &programLinkStatus);
        if(!programLinkStatus) {
            GLchar log[1024];
            glGetShaderInfoLog(m_ID, 1024, nullptr, log);
            std::cerr << "SHADER ERROR: link-time error\n" << log << std::endl;
        } else {
            m_isShadersCompiled = true;
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    bool ShaderProgram::createShader(const std::string &source, const GLenum shaderType, GLuint &shaderID) {
        shaderID = glCreateShader(shaderType);
        const char* code = source.c_str();
        glShaderSource(shaderID, 1, &code, nullptr);
        glCompileShader(shaderID);

        GLint shaderCompileStatus;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompileStatus);
        if (!shaderCompileStatus) {
            GLchar log[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, log);
            std::cerr << "SHADER ERROR: compile-time error:\n" << log << std::endl;
            return false;
        }
        return true;
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(m_ID);
    }

    void ShaderProgram::use() const {
        glUseProgram(m_ID);
    }

    ShaderProgram& ShaderProgram::operator = (ShaderProgram&& shaderProgram)  noexcept {
        glDeleteProgram(m_ID);
        m_ID = shaderProgram.m_ID;
        m_isShadersCompiled = shaderProgram.m_isShadersCompiled;

        shaderProgram.m_ID = 0;
        shaderProgram.m_isShadersCompiled = false;

        return *this;
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram)  noexcept {
        m_ID = shaderProgram.m_ID;
        m_isShadersCompiled = shaderProgram.m_isShadersCompiled;

        shaderProgram.m_ID = 0;
        shaderProgram.m_isShadersCompiled = false;
    }
}