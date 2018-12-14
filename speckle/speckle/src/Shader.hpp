#ifndef SPECKLE_SHADER_HPP
#define SPECKLE_SHADER_HPP

#include <string>

namespace speckle {

class Shader {
public:
  unsigned int ID;

  Shader(const std::string &vertexPath, const std::string &fragmentPath);

  void Use();

  void SetBool(const std::string &name, bool value) const;
  void SetInt(const std::string &name, int value) const;
  void SetFloat(const std::string &name, float value) const;
};

} // namespace speckle

#endif //SPECKLE_SHADER_HPP
