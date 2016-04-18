/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#pragma once

#include "Common.hpp"

struct BaseLight {
  BaseLight() : intensity(0) {}
  BaseLight(const glm::vec3 &color, float intensity)
      : color(color), intensity(intensity) {}
  glm::vec3 color;
  float intensity;
};

typedef BaseLight AmbientLight;

struct DirectionalLight {
  DirectionalLight() {}
  DirectionalLight(const glm::vec3 &color, float intensity,
                   const glm::vec3 &direction)
      : base(color, intensity), direction(direction) {}
  BaseLight base;
  glm::vec3 direction;
};
