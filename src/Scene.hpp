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

  std::shared_ptr<Camera> GetCamera();

  void AddNode(std::shared_ptr<Node> node);

  std::shared_ptr<Camera> m_camera;
  std::vector<std::shared_ptr<Node>> m_nodes;

  // scene lighting
  AmbientLight m_ambientLight;
  DirectionalLight m_directionalLight;
};
