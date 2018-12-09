#ifndef SPECKLE_LIBRARY_H
#define SPECKLE_LIBRARY_H

#include <functional>
namespace speckle {

class Renderer {
public:
  typedef void* (* ProcAddressFactoryFun)(const char *name);

  explicit Renderer(ProcAddressFactoryFun procAddressFactory);
  ~Renderer();
  void Resize(unsigned int width, unsigned int height);
  void Render();

private:
  using GlId = unsigned int;
  GlId itsShaderProgram = 0;
  GlId itsVAO = 0;
  GlId itsVBO = 0;
  GlId itsEBO = 0;
};

}   // namespace speckle

#endif