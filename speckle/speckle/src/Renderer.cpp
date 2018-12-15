#include "Renderer.h"
#include <iostream>

#include "glad/glad.h"
#include "stb/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.hpp"

namespace speckle {

using namespace std::chrono;

namespace {

glm::vec3 cubePositions[] = { // NOLINT(cert-err58-cpp)
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)
};

}

Renderer::Renderer(ProcAddressFactoryFun procAddressFactory) {
  if (!gladLoadGLLoader((GLADloadproc) procAddressFactory)) {
    std::cout << "Failed to init GLAD" << std::endl;
    return;
  }

  itsShader = std::make_unique<Shader>("resources/shaders/vertex.glsl",
                                       "resources/shaders/fragment.glsl");

  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
  };

  glGenVertexArrays(1, &itsVAO);
  glGenBuffers(1, &itsVBO);

  glBindVertexArray(itsVAO);

  glBindBuffer(GL_ARRAY_BUFFER, itsVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void *) nullptr);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void *) (3*sizeof(float)));
  glEnableVertexAttribArray(1);

  glEnable(GL_DEPTH_TEST);

  stbi_set_flip_vertically_on_load(true);
  itsBoardTexture = LoadTexture("resources/container.jpg", GL_RGB);
  itsFaceTexture = LoadTexture("resources/awesomeface.png", GL_RGBA);

  itsShader->Use();
  itsShader->SetInt("texture1", 0);
  itsShader->SetInt("texture2", 1);

  itsLastFrame = Clock::now();
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
  if (itsBoardTexture)
    glDeleteTextures(1, &itsBoardTexture);
}

void Renderer::Resize(unsigned int width, unsigned int height) {
  glViewport(0, 0, width, height);
  itsCamera.Resize(width, height);
}

void Renderer::Render() {
  itsDeltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(Clock::now() - itsLastFrame).count();

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT(hicpp-signed-bitwise)

  itsShader->Use();

  itsShader->SetMatrix("view", itsCamera.GetViewPort());
  itsShader->SetMatrix("projection", itsCamera.GetPerspective());

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, itsBoardTexture);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, itsFaceTexture);

  glBindVertexArray(itsVAO);

  for (auto i = 0; i < 10; ++i) {
    glm::mat4 model;
    model = glm::translate(model, cubePositions[i]);
    model = glm::rotate(model, glm::radians(20.0f*i), glm::vec3(1.0, 0.0, 0.0));
    itsShader->SetMatrix("model", glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  glBindVertexArray(0);

  itsLastFrame = Clock::now();
}

}   // namespace speckle