#ifndef SPECKLE_LIBRARY_H
#define SPECKLE_LIBRARY_H

#include <functional>
#include <memory>
#include <vector>

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
  using TextureType = int;
  unsigned int LoadTexture(const std::string &path, TextureType type) const;
  std::unique_ptr<Shader> itsShader;

  GlId itsVAO = 0;
  GlId itsVBO = 0;
  GlId itsBoardTexture = 0;
  GlId itsFaceTexture = 0;
};

}   // namespace speckle

#endif