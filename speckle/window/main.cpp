#include "Renderer.h"
#include "GLFW/glfw3.h"
#include <iostream>

using namespace speckle;

namespace {
  Renderer* renderer;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  renderer->Resize(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
      std::cout << "Failed to create window" << std::endl;
      glfwTerminate();
      return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Renderer r((Renderer::ProcAddressFactoryFun)glfwGetProcAddress);
    renderer = &r;

    while (!glfwWindowShouldClose(window)) {
      processInput(window);

      renderer->Render();

      glfwSwapBuffers(window);
      glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}