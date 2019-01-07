#include "rendering.hpp"
#include <vector>
#include <memory>
#include "glad/glad.h"
#include "Renderer.hpp"
#include "iostream"

namespace speckle {
namespace rendering {

namespace {
std::vector<std::unique_ptr<Renderer>> renderers;
bool hasInitializedGlad = false;
}

void InitializeWith(LoadProcess loading) {
  hasInitializedGlad = static_cast<bool>(gladLoadGLLoader(loading));
  if (!hasInitializedGlad)
    std::cerr << "Failed to init GLAD" << std::endl;
}

ID MakeRenderer() {
  if (!hasInitializedGlad) {
    hasInitializedGlad = static_cast<bool>(gladLoadGL());
    if (!hasInitializedGlad) {
      std::cerr << "Failed to init GLAD" << std::endl;
      return -1;
    }
  }

  auto id = renderers.size();
  renderers.emplace_back(std::make_unique<Renderer>());
  return static_cast<ID>(id);
}

void Render(ID self) {
  renderers[self]->Render();
}

void Resize(ID self, unsigned int width, unsigned int height) {
  renderers[self]->Resize(width, height);
}

void DisposeRenderer(ID self) {
  renderers[self] = nullptr;
}

} // namespace rendering
} // namespace speckle