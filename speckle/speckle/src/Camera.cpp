#include "Camera.hpp"
#include <algorithm>
#include <glm/gtc/type_ptr.hpp>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace speckle {

class Camera::Vec3 : public glm::vec3 {
public:
  Vec3() = default;
  Vec3(float x, float y, float z) : glm::vec3(x, y, z) {}
  Vec3(const Vec3 &other) = default;
  Vec3(Vec3 &&other) = default;
};

class Camera::Mat4 : public glm::mat4 {
public:
  Mat4() = default;
  Mat4(const Mat4 &other) = default;
  Mat4(Mat4 &&other) = default;
  explicit Mat4(const glm::mat4 &mat) : glm::mat4(mat) {}
};

namespace {
constexpr glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f); // NOLINT(cert-err58-cpp)
constexpr float Speed = 2.0f;
}

Camera::Camera() : Camera(Camera::Vec3(0.0f, 0.0f, 3.0f), 0.0f, -90.0f, 45.0f, 800.0f, 600.0f) {}

Camera::Camera(const Camera::Vec3 &position, float pitch, float yaw, float fov, float width, float height)
    : itsPosition(std::make_unique<Camera::Vec3>(position)), itsPitch(pitch), itsYaw(yaw), itsFov(fov), itsWidth(width),
      itsHeight(height) {
  CalcFront();
}

Camera::~Camera() = default;

void Camera::CalcFront() {
  itsFront = std::make_unique<Vec3>(
      std::cos(glm::radians(itsYaw))*std::cos(glm::radians(itsPitch)),
      std::sin(glm::radians(itsPitch)),
      std::sin(glm::radians(itsYaw))*std::cos(glm::radians(itsPitch)));
}

void Camera::Forward(float deltaTime) {
  *itsPosition += (*itsFront)*Speed*deltaTime;
}

void Camera::Back(float deltaTime) {
  *itsPosition -= (*itsFront)*Speed*deltaTime;
}

void Camera::Left(float deltaTime) {
  *itsPosition -= glm::normalize(glm::cross(*itsFront, Up))*Speed*deltaTime;
}

void Camera::Right(float deltaTime) {
  *itsPosition += glm::normalize(glm::cross(*itsFront, Up))*Speed*deltaTime;
}

void Camera::Rotate(float deltaPitch, float deltaYaw) {
  itsPitch = std::clamp(itsPitch + deltaPitch, -89.0f, 89.0f);
  itsYaw += deltaYaw;
  CalcFront();
}

void Camera::Zoom(float delta) {
  itsFov = std::clamp(itsFov - delta, 1.0f, 45.0f);
}

void Camera::Resize(float width, float height) {
  itsWidth = width;
  itsHeight = height;
}

float *Camera::GetViewPort() {
  itsView = std::make_unique<Mat4>(glm::lookAt(*itsPosition, *itsPosition + *itsFront, Up));
  auto &tmp = static_cast<glm::mat4 &>(*itsView);
  return glm::value_ptr(tmp);
}

float *Camera::GetPerspective() {
  itsPerspective = std::make_unique<Mat4>(glm::perspective(glm::radians(itsFov), itsWidth/itsHeight, 0.1f, 100.0f));
  auto &tmp = static_cast<glm::mat4 &>(*itsPerspective);
  return glm::value_ptr(tmp);
}

} // namespace speckle
