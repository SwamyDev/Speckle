#include "rendering.hpp"
#include <vector>
#include <memory>
#include "Renderer.hpp"

namespace speckle {
namespace rendering {

namespace {
std::vector<std::unique_ptr<Renderer>> renderers;
}
ID MakeRenderer(ProcAddressFactoryFun procAddressFactory) {
  auto id = renderers.size();
  renderers.emplace_back(std::make_unique<Renderer>(procAddressFactory));
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