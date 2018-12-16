#ifndef SPECKLE_LIBRARY_H
#define SPECKLE_LIBRARY_H

namespace speckle {

class Renderer {
public:
  using ColorType = unsigned int;

  Renderer();
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