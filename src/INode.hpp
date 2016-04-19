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

  // mothods required by game logic
  virtual bool isDestroyRequested() = 0;
  virtual void CheckContacts() = 0;
};
