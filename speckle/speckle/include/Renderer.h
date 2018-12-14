#ifndef SPECKLE_LIBRARY_H
#define SPECKLE_LIBRARY_H

#include <functional>
#include <memory>

namespace speckle {

class Shader;

class Renderer {
public:
  typedef void* (* ProcAddressFactoryFun)(const char *name);

  explicit Renderer(ProcAddressFactoryFun procAddressFactory);
  ~Renderer();
  void Resize(unsigned int width, unsigned int height);
  void Render();

private:
  using GlId = unsigned int;
  std::unique_ptr<Shader> itsShader;
  GlId itsVAO = 0;
  GlId itsVBO = 0;
  GlId itsEBO = 0;
};

}   // namespace speckle

#endif