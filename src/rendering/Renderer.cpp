/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "rendering/Renderer.hpp"
#include "game/PhysicsSimulator.hpp"
#include "game/SpaceShip.hpp"
#include "rendering/Quad.hpp"
#include "rendering/TextRenderer.hpp"

static TextRenderer s_textRenderer;

Renderer::Renderer() {
  LOGD("Created renderer");

  m_shader =
      std::make_shared<ShaderProgram>("res/diffuse.vsh", "res/diffuse.fsh");

  m_shader->RegisterUniform("u_mvp");
  m_shader->RegisterUniform("u_transform");

  m_shader->RegisterUniform("u_ambientLight.color");
  m_shader->RegisterUniform("u_ambientLight.intensity");

  m_shader->RegisterUniform("u_directionalLight.base.color");
  m_shader->RegisterUniform("u_directionalLight.base.intensity");
  m_shader->RegisterUniform("u_directionalLight.direction");

  m_starShader =
      std::make_shared<ShaderProgram>("res/stars.vsh", "res/stars.fsh");
  m_starShader->RegisterUniform("u_time");
  m_starShader->RegisterUniform("u_starRadius");
  m_starShader->RegisterUniform("u_starColor");
  m_starShader->RegisterUniform("u_starDensity");
  m_starShader->RegisterUniform("u_speed");
  m_starShader->RegisterUniform("u_resolution");

  m_projectileShader = std::make_shared<ShaderProgram>("res/projectile.vsh",
                                                       "res/projectile.fsh");
  m_projectileShader->RegisterUniform("u_mvp");
  m_projectileShader->RegisterUniform("u_transform");
  m_projectileShader->RegisterUniform("u_color");
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

  // Paralax star SSE
  m_starShader->BindProgram();
  m_starShader->SetUniform("u_starRadius", 0.8f);
  m_starShader->SetUniform("u_starColor", glm::vec3(1, 1, 1));
  m_starShader->SetUniform("u_starDensity", 3.5f);
  m_starShader->SetUniform("u_speed", 1.5f);
  m_starShader->SetUniform("u_resolution", glm::vec2(5, 7));

  m_projectileShader->BindProgram();
  m_projectileShader->SetUniform("u_color", glm::vec3(0, 1, 0));

  s_textRenderer.InitRenderer(32);
}

void Renderer::RenderScene() {
  // FB initialization
  glDepthMask(GL_TRUE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 0, 0);

  // SSE
  m_starShader->BindProgram();
  m_starShader->SetUniform("u_time", g_timer.GetTotalTime());
  static Quad q;
  q.Render();

  glEnable(GL_DEPTH_TEST);

  m_shader->BindProgram();
  m_shader->SetUniform("u_mvp", m_scene->GetCamera()->GetMVP());

  if (m_scene->m_spaceShip) {
    m_shader->SetUniform("u_transform",
                         m_scene->m_spaceShip->GetTransformation());
    m_scene->m_spaceShip->Draw();
  }

  for (auto &node : m_scene->m_asteroids) {
    m_shader->SetUniform("u_transform", node->GetTransformation());
    node->Draw();
  }

  m_projectileShader->BindProgram();
  m_projectileShader->SetUniform("u_mvp", m_scene->GetCamera()->GetMVP());
  for (auto &node : m_scene->m_projectiles) {
    m_projectileShader->SetUniform("u_transform", node->GetTransformation());
    node->Draw();
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  std::stringstream ss;
  ss << "Score: ";
  ss << SpaceShip::s_hitCount;
  s_textRenderer.RenderText(glm::vec3(0, -0.9, 0), 0.08f, glm::vec3(1, 1, 1),
                            ss.str());
  glDisable(GL_BLEND);

#ifdef GAME_DEBUG
  g_physics.DebugDraw();
#endif

  // unbind shader
  glUseProgram(0);
  glDepthMask(GL_FALSE);
  glDisable(GL_DEPTH_TEST);
}

void Renderer::Resize(float, float) {}
