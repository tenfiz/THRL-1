#ifndef THRL_1_SHADERPROGRAM_H
#define THRL_1_SHADERPROGRAM_H

#include <glad/glad.h>
#include <iostream>
#include <string>

namespace Renderer {
    class ShaderProgram {
    public:
        ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader);
        ~ShaderProgram();

        ShaderProgram() = delete;
        ShaderProgram(ShaderProgram&) = delete;
        ShaderProgram& operator = (const ShaderProgram&) = delete;
        ShaderProgram& operator = (ShaderProgram&& shaderProgram) noexcept;
        ShaderProgram(ShaderProgram&& ShaderProgram) noexcept;

        bool isShadersCompiled() const { return m_isShadersCompiled; }
        void use() const;

    private:
        bool createShader(const std::string &source, const GLenum shaderType, GLuint &shaderID);

        bool m_isShadersCompiled = false;
        GLuint m_ID = 0;
    };
}


#endif //THRL_1_SHADERPROGRAM_H
