#include "Renderer.h"
#include <iostream>
#include <chrono>

#include "glad/glad.h"
#include "stb/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.hpp"

namespace speckle {

using namespace std::chrono;

namespace {
high_resolution_clock::time_point initTime; // NOLINT(cert-err58-cpp)
}

Renderer::Renderer(ProcAddressFactoryFun procAddressFactory) {
  if (!gladLoadGLLoader((GLADloadproc) procAddressFactory)) {
    std::cout << "Failed to init GLAD" << std::endl;
    return;
  }

  itsShader = std::make_unique<Shader>("resources/shaders/vertex.glsl",
                                       "resources/shaders/fragment.glsl");

  stbi_set_flip_vertically_on_load(true);
  itsBoardTexture = LoadTexture("resources/container.jpg", GL_RGB);
  itsFaceTexture = LoadTexture("resources/awesomeface.png", GL_RGBA);

  float vertices[] = {
      0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
      0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *) nullptr);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *) (3*sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *) (6*sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  itsShader->Use();
  itsShader->SetInt("texture1", 0);
  itsShader->SetInt("texture2", 1);

  initTime = high_resolution_clock::now();
}

unsigned int Renderer::LoadTexture(const std::string &path, TextureType type) const {
  int width, height, channels;
  unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  if (!data) {
    std::cerr << "Failed to load texture" << std::endl;
    return 0;
  }

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, type, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(data);
  return texture;
}

Renderer::~Renderer() {
  if (itsVAO)
    glDeleteVertexArrays(1, &itsVAO);
  if (itsVBO)
    glDeleteBuffers(1, &itsVBO);
  if (itsEBO)
    glDeleteBuffers(1, &itsEBO);
  if (itsBoardTexture)
    glDeleteTextures(1, &itsBoardTexture);
}

void Renderer::Resize(unsigned int width, unsigned int height) {
  glViewport(0, 0, width, height);
}

void Renderer::Render() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  itsShader->Use();

  auto t = high_resolution_clock::now();
  auto time = duration_cast<duration<float>>(t - initTime);
  glm::mat4 trans;
  trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
  trans = glm::rotate(trans, time.count(), glm::vec3(0.0, 0.0, 1.0));
  itsShader->SetMatrix("transform", glm::value_ptr(trans));

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, itsBoardTexture);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, itsFaceTexture);

  glBindVertexArray(itsVAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
}

}   // namespace speckle