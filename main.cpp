#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer/ShaderProgram.h"

using namespace std;


// |--IMPORTANT!----------------------------------------------------------------------------------------
// | The code will be completely rewritten. Therefore, it is better not to read this code without beer |
// | Now the code draw a multicolored right triangle on a red background                               |
// | The code uses standard OpenGL initialization, taken from the glad documentation                   |
// |----------------------------------------------------------------------------------------------------

int glfwWindowWidth = 640;
int glfwWindowHeight = 480;

GLfloat point[] = {
        0.5f, 0.5f, 0.0f,
        0.5, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.5f
};

GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
};

const char* vertexShader =
        "#version 330\n"
        "layout(location = 0) in vec3 vertex_position;"
        "layout(location = 1) in vec3 vertex_color;"
        "out vec3 color;"
        "void main() {"
        "   color = vertex_color;"
        "   gl_Position = vec4(vertex_position, 1.0);"
        "}";

const char* fragmentShader =
        "#version 330\n"
        "in vec3 color;"
        "out vec4 frag_color;"
        "void main() {"
        "   frag_color = vec4(color, 1.0);"
        "}";

void glfwWindowSizeCallback([[maybe_unused]] GLFWwindow* pWindow, int width, int height) {
    glfwWindowWidth = width;
    glfwWindowHeight = height;
    glViewport(0, 0, glfwWindowWidth, glfwWindowHeight);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
}

int main() {
    if (!glfwInit()) {
        cerr << "glfw init failed!" << endl;
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* pWindow = glfwCreateWindow(glfwWindowWidth, glfwWindowHeight, "OpenGL Game", nullptr, nullptr);
    if (!pWindow) {
        cerr << "glfwCreateWindow failed!" << endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    glfwMakeContextCurrent(pWindow);

    if(!gladLoadGL()) {
        std::cerr << "Cant load GLAD!" << std::endl;
    }

    cout << "Render: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

    glClearColor(0.6, 0.1, 0.2, 1);

    std::string _vertexShader(vertexShader);
    std::string  _fragmentShader(fragmentShader);
    Renderer::ShaderProgram shaderProgram(_vertexShader, _fragmentShader);
    if (!shaderProgram.isShadersCompiled()) {
        cerr << "Can't create shader program" << endl;
        return -1;
    }

    GLuint pointsVertexBufferObject = 0;
    glGenBuffers(1, &pointsVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

    GLuint colorsVertexBufferObject = 0;
    glGenBuffers(1, &colorsVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint vertexArrayObject = 0;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVertexBufferObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVertexBufferObject);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    while (!glfwWindowShouldClose(pWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(pWindow);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}