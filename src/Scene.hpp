/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#pragma once

#include "Common.hpp"
#include "INode.hpp"
#include "rendering/Camera.hpp"
#include "rendering/Lights.hpp"

#include <vector>

class Scene {
 public:
  Scene();
  ~Scene();

  void Init(std::shared_ptr<Camera> camera);
  void Update(float dt);
  void Reset();

  std::shared_ptr<Camera> GetCamera();

  std::shared_ptr<Camera> m_camera;

  std::shared_ptr<INode> m_spaceShip;
  std::vector<std::shared_ptr<INode>> m_asteroids;
  std::vector<std::shared_ptr<INode>> m_projectiles;

  // scene lighting
  AmbientLight m_ambientLight;
  DirectionalLight m_directionalLight;
};
