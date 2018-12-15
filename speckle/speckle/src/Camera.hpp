#ifndef SPECKLE_CAMERA_HPP
#define SPECKLE_CAMERA_HPP

#include <memory>

namespace speckle {

class Camera {
public:
  class Vec3;
  class Mat4;

  Camera();
  Camera(const Vec3 &position, float pitch, float yaw, float fov, float width, float height);
  ~Camera();

  void Forward(float deltaTime);
  void Back(float deltaTime);
  void Left(float deltaTime);
  void Right(float deltaTime);

  void Rotate(float deltaPitch, float deltaYaw);
  void Zoom(float delta);
  void Resize(float width, float height);

  float *GetViewPort();
  float *GetPerspective();

private:
  void CalcFront();

  std::unique_ptr<Vec3> itsPosition;
  std::unique_ptr<Vec3> itsFront;
  float itsPitch;
  float itsYaw;

  float itsFov;
  float itsWidth;
  float itsHeight;

  std::unique_ptr<Mat4> itsView;
  std::unique_ptr<Mat4> itsPerspective;
};

} // namspace speckle

#endif //SPECKLE_CAMERA_HPP
