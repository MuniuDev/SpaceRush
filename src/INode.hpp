/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#pragma once

#include "Common.hpp"

class INode {
 public:
  virtual void Init() = 0;
  virtual void Update(float dt) = 0;
  virtual void Draw() = 0;
  virtual glm::mat4 GetTransformation() const = 0;
  virtual bool isDestroyRequested() = 0;

  /*virtual void SetPos(const glm::vec3 &pos) = 0;
  virtual void SetRot(const glm::quat &rot) = 0;
  virtual void Move(const glm::vec3 &dir) = 0;
  virtual void Rotate(const glm::quat &rot) = 0;*/
};
