#include "Renderer.h"
#include "GLFW/glfw3.h"
#include <iostream>

using namespace speckle;

namespace {

Renderer *renderer;
float lastX = 0.0f, lastY = 0.0f;
bool isFirstMouse = true;

}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  renderer->Resize(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
}

void mouse_callback(GLFWwindow *window, double xPos, double yPos) {
  if (isFirstMouse) {
    lastX = static_cast<float>(xPos);
    lastY = static_cast<float>(yPos);
    isFirstMouse = false;
  }

  auto xOffset = static_cast<float>(xPos - lastX);
  auto yOffset = static_cast<float>(lastY - yPos);
  lastX = static_cast<float>(xPos);
  lastY = static_cast<float>(yPos);

  constexpr float sensitivity = 0.05f;
  xOffset *= sensitivity;
  yOffset *= sensitivity;

  renderer->GetCamera().Rotate(yOffset, xOffset);
}

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset) {
  renderer->GetCamera().Zoom(static_cast<float>(yOffset));
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS)
    renderer->Forward();
  if (glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS)
    renderer->Back();
  if (glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS)
    renderer->Left();
  if (glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS)
    renderer->Right();
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "Speckle", nullptr, nullptr);
  if (window==nullptr) {
    std::cout << "Failed to create window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  {
    Renderer r((Renderer::ProcAddressFactoryFun) glfwGetProcAddress);
    renderer = &r;
    renderer->Resize(800, 600);

    while (!glfwWindowShouldClose(window)) {
      processInput(window);

      renderer->Render();

      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  }

  glfwTerminate();
  return 0;
}