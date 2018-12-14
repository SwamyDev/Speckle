#include "Renderer.h"
#include <iostream>

#include "glad/glad.h"
#include "Shader.hpp"

namespace speckle {

Renderer::Renderer(ProcAddressFactoryFun procAddressFactory) {
  if (!gladLoadGLLoader((GLADloadproc) procAddressFactory)) {
    std::cout << "Failed to init GLAD" << std::endl;
    return;
  }

  itsShader = std::make_unique<Shader>("/home/bernhard/repos/Speckle/speckle/speckle/src/vertex.glsl",
                                       "/home/bernhard/repos/Speckle/speckle/speckle/src/fragment.glsl");

  float vertices[] = {
      0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
      -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f
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

  glVertexAttribPointer(0,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        6*sizeof(float),
                        (void *) 0); // NOLINT(modernize-use-nullptr) We actually mean the value 0 here
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *) (3*sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

Renderer::~Renderer() {
  if (itsVAO)
    glDeleteVertexArrays(1, &itsVAO);
  if (itsVBO)
    glDeleteBuffers(1, &itsVBO);
  if (itsEBO)
    glDeleteBuffers(1, &itsEBO);
}

void Renderer::Resize(unsigned int width, unsigned int height) {
  glViewport(0, 0, width, height);
}

void Renderer::Render() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  itsShader->Use();

  glBindVertexArray(itsVAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
}

}   // namespace speckle
#pragma clang diagnostic pop