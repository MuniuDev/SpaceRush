/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#pragma once

#include <SDL.h>
#undef main

#define GLEW_STATIC  // Link GLEW in static mode
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

#ifdef __APPLE__  // OSX
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#elif __WIN32__  // Windows
#include <gl/gl.h>
#include <gl/glu.h>
#else  // Linux
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common/Input.hpp"
#include "common/Logger.hpp"
#include "common/Timer.hpp"

#include <algorithm>
#include <map>
#include <random>
#include <sstream>

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <memory>

typedef int32_t int_t;
typedef int64_t long_t;
typedef uint32_t uint_t;
typedef uint64_t ulong_t;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

#ifndef M_PI_4
#define M_PI_4 0.78539816339744830962
#endif

inline std::string ErrorStr(GLenum err) {
  std::string error;

  switch (err) {
    case GL_INVALID_OPERATION:
      error = "INVALID_OPERATION";
      break;
    case GL_INVALID_ENUM:
      error = "INVALID_ENUM";
      break;
    case GL_INVALID_VALUE:
      error = "INVALID_VALUE";
      break;
    case GL_OUT_OF_MEMORY:
      error = "OUT_OF_MEMORY";
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      error = "INVALID_FRAMEBUFFER_OPERATION";
      break;
  }

  return error;
}

inline void CheckGLError(const char *file, int line) {
  GLenum err = GL_NO_ERROR;
  while ((err = glGetError()) != GL_NO_ERROR) {
    LOGE("{}:{} OpenGL error: [{}] {}", file, line, err, ErrorStr(err));
  }
}

inline float GetRandom() { return rand() % 1000 / 1000.0f; }

inline std::string GetPath(std::string path) {
#ifdef __WIN32__
  std::replace(path.begin(), path.end(), '/', '\\');
#endif  // __WIN32__

  return path;
}

#define CHECK_GL_ERR() CheckGLError(__FILE__, __LINE__)
