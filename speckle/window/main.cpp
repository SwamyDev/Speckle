#include "rendering.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

using namespace speckle;

class RenderingRAII {
public:
  RenderingRAII() {
    itsRenderer = rendering::MakeRenderer();
    if (itsRenderer==-1)
      exit(1);
  }

  ~RenderingRAII() {
    rendering::DisposeRenderer(itsRenderer);
  }

  void Resize(unsigned int width, unsigned int height) {
    rendering::Resize(itsRenderer, width, height);
  }

  void Render() {
    rendering::Render(itsRenderer);
  }

private:
  rendering::ID itsRenderer;
};

namespace {
RenderingRAII *render;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  render->Resize(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "Speckle", nullptr, nullptr);
  if (window==nullptr) {
    std::cout << "Failed to create window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  rendering::InitializeWith((rendering::LoadProcess) glfwGetProcAddress);
  {
    RenderingRAII r;
    render = &r;

    while (!glfwWindowShouldClose(window)) {
      processInput(window);

      r.Render();

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }

  glfwTerminate();
  return 0;
}