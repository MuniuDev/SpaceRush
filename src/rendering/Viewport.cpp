/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "rendering/Viewport.hpp"

Viewport::Viewport(float width, float height)
    : m_width(width), m_height(height), m_camera(nullptr) {}

void Viewport::Resize(float width, float height) {
  LOGD("Resizing viewport to {}x{}", width, height);
  m_width = width;
  m_height = height;
  m_camera->Resize(45.0f, m_width / m_height, 0.1f, 1000.0f);

  m_renderer->Resize(m_width, m_height);
}

void Viewport::Init(std::shared_ptr<Scene> scene) {
  m_camera = std::make_shared<Camera>(45.0f, m_width / m_height, 0.1f, 1000.0f);
  m_scene = scene;
  m_scene->Init(m_camera);
  m_renderer = std::make_shared<Renderer>();
  m_renderer->InitRenderer(m_scene, m_width, m_height);
  CHECK_GL_ERR();
}

void Viewport::Draw() {
  if (!m_scene) return;
  glViewport(0, 0, (GLsizei)m_width, (GLsizei)m_height);
  m_renderer->RenderScene();
}
