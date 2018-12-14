#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include "glad/glad.h"

namespace speckle {

namespace {

using ShaderType = unsigned int;
constexpr size_t LogSize = 512;


std::string ReadShaderSource(const std::string& path) {
  std::ifstream file;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    file.open(path);
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
  } catch (std::ifstream::failure& failure) {
    std::cerr << "ERROR::SHADER::IO_FAILED\nCouldn't read file: " << path << std::endl;
    return {};
  }
}

unsigned int CompileShader(const std::string& source, ShaderType type) {
  auto id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[LogSize];
    glGetShaderInfoLog(id, LogSize, nullptr, infoLog);
    std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  return id;
}

}

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
  auto vertexSource = ReadShaderSource(vertexPath);
  auto fragmentSource = ReadShaderSource(fragmentPath);

  auto vertex = CompileShader(vertexSource, GL_VERTEX_SHADER);
  auto fragment = CompileShader(fragmentSource, GL_FRAGMENT_SHADER);

  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);

  int success;
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[LogSize];
    glGetProgramInfoLog(ID, LogSize, nullptr, infoLog);
    std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::Use() {
  glUseProgram(ID);
}

void Shader::SetBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

} // namespace speckle
