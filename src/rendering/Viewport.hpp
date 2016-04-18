/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#pragma once

#include <memory>
#include <unordered_map>

#include "Common.hpp"
#include "Scene.hpp"
#include "rendering/Camera.hpp"
#include "rendering/Renderer.hpp"
#include "rendering/ShaderProgram.hpp"

class Viewport {
 public:
  Viewport(float width, float height);

  void Init(std::shared_ptr<Scene> scene);
  void Resize(float width, float height);
  void Draw();

 private:
  float m_width;
  float m_height;

  std::shared_ptr<Scene> m_scene;  // current scene
  std::shared_ptr<Camera> m_camera;
  std::shared_ptr<Renderer> m_renderer;  // current renderer
};
