#ifndef SPECKLE_LIBRARY_H
#define SPECKLE_LIBRARY_H

#include <functional>
#include <memory>
#include <vector>
#include <chrono>
#include "../src/Camera.hpp"

namespace speckle {

class Shader;

class Renderer {
public:
  typedef void *(*ProcAddressFactoryFun)(const char *name);

  explicit Renderer(ProcAddressFactoryFun procAddressFactory);
  ~Renderer();
  void Resize(unsigned int width, unsigned int height);
  void Render();

  void Forward() { itsCamera.Forward(itsDeltaTime); }
  void Back() { itsCamera.Back(itsDeltaTime); }
  void Left() { itsCamera.Left(itsDeltaTime); }
  void Right() { itsCamera.Right(itsDeltaTime); }

  Camera &GetCamera() { return itsCamera; }

private:
  using GlId = unsigned int;
  using TextureType = int;
  using Clock = std::chrono::high_resolution_clock;

  unsigned int LoadTexture(const std::string &path, TextureType type) const;
  std::unique_ptr<Shader> itsShader;

  GlId itsVAO = 0;
  GlId itsVBO = 0;
  GlId itsBoardTexture = 0;
  GlId itsFaceTexture = 0;

  Camera itsCamera;

  float itsDeltaTime = 0.0f;
  Clock::time_point itsLastFrame;
};

}   // namespace speckle

#endif