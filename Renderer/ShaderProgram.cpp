#include "ShaderProgram.h"

namespace Renderer {
    ShaderProgram::ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader) {
        // Compile vertex shader
        GLuint vertexShaderID;
        if (!compileShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)) {
            std::cerr << "VERTEX SHADER: compile-time error" << std::endl;
            return;
        }

        // Compile fragment shader
        GLuint fragmentShaderID;
        if (!compileShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {
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
            glGetProgramInfoLog(m_ID, 1024, nullptr, log);
            std::cerr << "SHADER ERROR: link-time error\n" << log << std::endl;
        } else {
            // Shader program was created
            m_isShadersCompiled = true;
        }

        // Delete the shaders, because the shader program has already been created
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }
    bool ShaderProgram::compileShader(const std::string &source, const GLenum shaderType, GLuint &shaderID) {
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