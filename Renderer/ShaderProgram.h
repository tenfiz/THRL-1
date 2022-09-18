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

        ShaderProgram() = delete;    // You cannot create a shader program without source code
        ShaderProgram(ShaderProgram&) = delete;    // You cannot create a shader program using another shader program
        ShaderProgram& operator = (const ShaderProgram&) = delete;    // You cannot equate one shader program to another
        ShaderProgram& operator = (ShaderProgram&& shaderProgram) noexcept;    // Summon operator
        ShaderProgram(ShaderProgram&& shaderProgram) noexcept;    // Summon instructor

        [[nodiscard]] bool isShadersCompiled() const { return m_isShadersCompiled; }
        void use() const;

    private:
        static bool compileShader(const std::string &source, GLenum shaderType, GLuint &shaderID);

        bool m_isShadersCompiled = false;
        GLuint m_ID = 0;
    };
}


#endif //THRL_1_SHADERPROGRAM_H
