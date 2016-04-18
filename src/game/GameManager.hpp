/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#pragma once

#include "Scene.hpp"

class GameManager {
 public:
  GameManager(std::shared_ptr<Scene> scene);
  ~GameManager();

  void Init();
  void Reset();
  void Update();

 private:
  std::shared_ptr<Scene> m_scene;
};
