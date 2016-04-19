/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "Scene.hpp"

Scene::Scene() : m_camera(nullptr) {
  // basic scene lights
  m_ambientLight = AmbientLight(glm::vec3(1, 1, 1), 1.00f);
  m_directionalLight = DirectionalLight(glm::vec3(1, 1, 1), 0.0f,
                                        glm::normalize(glm::vec3(1, -1, 1)));
}

Scene::~Scene() {}

void Scene::Init(std::shared_ptr<Camera> camera) {
  m_camera = camera;

  m_camera->SetPos(glm::vec3(0, 0, 20));
  // m_camera->SetRotate(glm::quat(0, 0, 0, 1));
}

void Scene::Update(float dt) {
  m_camera->HandleInput(dt);
  if (m_spaceShip) m_spaceShip->Update(dt);

  for (auto &node : m_asteroids) {
    node->Update(dt);
  }

  for (auto &node : m_projectiles) {
    node->Update(dt);
  }
}

std::shared_ptr<Camera> Scene::GetCamera() { return m_camera; }
