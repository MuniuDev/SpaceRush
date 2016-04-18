/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "rendering/Renderer.hpp"

#define MAX_POINT_LIGHT 10

Renderer::Renderer() {
  LOGD("Created renderer");

  m_shader = std::make_shared<ShaderProgram>("res/basic.vsh", "res/basic.fsh");

  m_shader->RegisterUniform("u_mvp");
  m_shader->RegisterUniform("u_transform");

  m_shader->RegisterUniform("u_ambientLight.color");
  m_shader->RegisterUniform("u_ambientLight.intensity");

  m_shader->RegisterUniform("u_directionalLight.base.color");
  m_shader->RegisterUniform("u_directionalLight.base.intensity");
  m_shader->RegisterUniform("u_directionalLight.direction");
}

Renderer::~Renderer() {}

void Renderer::InitRenderer(std::shared_ptr<Scene> scene, float, float) {
  m_scene = scene;

  m_shader->BindProgram();

  m_shader->SetUniform("u_ambientLight.color", m_scene->m_ambientLight.color);
  m_shader->SetUniform("u_ambientLight.intensity",
                       m_scene->m_ambientLight.intensity);

  m_shader->SetUniform("u_directionalLight.base.color",
                       m_scene->m_directionalLight.base.color);
  m_shader->SetUniform("u_directionalLight.base.intensity",
                       m_scene->m_directionalLight.base.intensity);
  m_shader->SetUniform("u_directionalLight.direction",
                       m_scene->m_directionalLight.direction);
}

void Renderer::RenderScene() {
  // FB initialization
  glDepthMask(GL_TRUE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 0, 0);
  glEnable(GL_DEPTH_TEST);

  m_shader->BindProgram();
  m_shader->SetUniform("u_mvp", m_scene->GetCamera()->GetMVP());

  for (auto &node : m_scene->m_nodes) {
    node->Draw();
  }

  // unbind shader
  glUseProgram(0);
  glDepthMask(GL_FALSE);
  glDisable(GL_DEPTH_TEST);
}

void Renderer::Resize(float, float) {}
