/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "rendering/ShaderProgram.hpp"

#include <fstream>
#include <vector>

std::string ArrayUniformName(const std::string &name, const std::string &field,
                             int idx) {
  std::stringstream ss("");
  ss << name;
  ss << "[";
  ss << idx;
  ss << "].";
  ss << field;
  return ss.str();
}

ShaderProgram::ShaderProgram(const std::string &vertexShader,
                             const std::string &fragmentShader) {
  m_program = glCreateProgram();
  if (m_program == 0) {
    LOGE("Creation of shader program failed! Exiting...");
    std::exit(-1);
  }
  LoadShader(GL_VERTEX_SHADER, vertexShader);
  LoadShader(GL_FRAGMENT_SHADER, fragmentShader);
  CompileProgram();
}

void ShaderProgram::BindProgram() const { glUseProgram(m_program); }

void ShaderProgram::CompileProgram() {
  glLinkProgram(m_program);
  int linkStatus = 0;

  glGetProgramiv(m_program, GL_LINK_STATUS, &linkStatus);

  if (linkStatus == 0) {
    int infoLogLength = 0;
    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> errorMessage;
    errorMessage.resize(infoLogLength + 1);
    glGetProgramInfoLog(m_program, infoLogLength, NULL, &errorMessage[0]);
    LOGE("Program linking: {}", std::string(&errorMessage[0]));
    std::exit(-1);
  }
}

void ShaderProgram::Validate() {
  int status = 0;
  glValidateProgram(m_program);

  glGetProgramiv(m_program, GL_VALIDATE_STATUS, &status);
  if (status == 0) {
    int infoLogLength = 0;
    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> errorMessage;
    errorMessage.resize(infoLogLength + 1);
    glGetProgramInfoLog(m_program, infoLogLength, NULL, &errorMessage[0]);
    LOGE("Program validation: {}", std::string(&errorMessage[0]));
    std::exit(-1);
  }
}

std::string ShaderProgram::LoadShaderCode(const std::string &shaderName) const {
  std::ifstream ifs(shaderName);
  std::string source((std::istreambuf_iterator<char>(ifs)),
                     (std::istreambuf_iterator<char>()));
  return source;
}

void ShaderProgram::LoadShader(int type, const std::string &shaderName) {
  int shader = glCreateShader(type);
  if (shader == 0) {
    LOGE("Creation of shader failed! Exiting...");
    std::exit(-1);
  }

  std::string shaderCode = LoadShaderCode(shaderName);

  const char *code = shaderCode.c_str();
  glShaderSource(shader, 1, &code, NULL);
  glCompileShader(shader);

  int compileStatus = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

  if (compileStatus == 0) {
    int infoLogLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> errorMessage;
    errorMessage.resize(infoLogLength + 1);
    glGetShaderInfoLog(shader, infoLogLength, NULL, &errorMessage[0]);
    LOGE("Shader compilation: {}", std::string(&errorMessage[0]));
    std::exit(-1);
  }

  glAttachShader(m_program, shader);
  glDeleteShader(shader);  // is it ok to do it here?
  CHECK_GL_ERR();
}

GLuint ShaderProgram::GetProgramHandle() const { return m_program; }

void ShaderProgram::RegisterUniform(const std::string &name) {
  GLint tmp = 0;
  tmp = glGetUniformLocation(m_program, name.c_str());
  if (tmp == -1) {
    LOGE("Invalid uniform location for {}", name);
    return;
  }
  m_uniforms[name] = tmp;
  CHECK_GL_ERR();
}

void ShaderProgram::SetUniform(const std::string &name, int val) {
  glUniform1i(m_uniforms[name], val);
}

void ShaderProgram::SetUniform(const std::string &name, float val) {
  glUniform1f(m_uniforms[name], val);
}

void ShaderProgram::SetUniform(const std::string &name, const glm::vec2 &val) {
  glUniform2f(m_uniforms[name], val.x, val.y);
}

void ShaderProgram::SetUniform(const std::string &name, const glm::vec3 &val) {
  glUniform3f(m_uniforms[name], val.x, val.y, val.z);
}

void ShaderProgram::SetUniform(const std::string &name, const glm::mat4 &val) {
  glUniformMatrix4fv(m_uniforms[name], 1, GL_FALSE, glm::value_ptr(val));
}
