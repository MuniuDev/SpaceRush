/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#pragma once

#include "Common.hpp"
#include "Scene.hpp"
#include "rendering/ShaderProgram.hpp"

class Renderer {
 public:
  Renderer();
  virtual ~Renderer();

  virtual void InitRenderer(std::shared_ptr<Scene> scene, float, float);
  virtual void RenderScene();
  virtual void Resize(float, float);

 protected:
  std::shared_ptr<Scene> m_scene;
  std::shared_ptr<ShaderProgram> m_shader;
};
