#include "Renderer.h"
#include <iostream>
#include <Renderer.h>

#include "glad/glad.h"

namespace speckle {

namespace {

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";
}

Renderer::Renderer(ProcAddressFactoryFun procAddressFactory) {
  if (!gladLoadGLLoader((GLADloadproc)procAddressFactory)) {
    std::cout << "Failed to init GLAD" << std::endl;
    return;
  }

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  itsShaderProgram = glCreateProgram();
  glAttachShader(itsShaderProgram, vertexShader);
  glAttachShader(itsShaderProgram, fragmentShader);
  glLinkProgram(itsShaderProgram);

  glGetProgramiv(itsShaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(itsShaderProgram, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float vertices[] = {
      0.5f,  0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      -0.5f, -0.5f, 0.0f,
      -0.5f,  0.5f, 0.0f
  };

  unsigned int indices[] = {
      0, 1, 3,
      1, 2, 3
  };

  glGenVertexArrays(1, &itsVAO);
  glGenBuffers(1, &itsVBO);
  glGenBuffers(1, &itsEBO);

  glBindVertexArray(itsVAO);

  glBindBuffer(GL_ARRAY_BUFFER, itsVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, itsEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) nullptr);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

Renderer::~Renderer() {
  if (itsVAO) glDeleteVertexArrays(1, &itsVAO);
  if (itsVBO) glDeleteBuffers(1, &itsVBO);
  if (itsEBO) glDeleteBuffers(1, &itsEBO);
}

void Renderer::Resize(unsigned int width, unsigned int height) {
  glViewport(0, 0, width, height);
}

void Renderer::Render() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(itsShaderProgram);
  glBindVertexArray(itsVAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
}

}   // namespace speckle