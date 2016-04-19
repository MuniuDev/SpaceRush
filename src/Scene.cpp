/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "Scene.hpp"
#include "game/SpaceShip.hpp"

Scene::Scene() : m_camera(nullptr) {
  // basic scene lights
  m_ambientLight = AmbientLight(glm::vec3(1, 1, 1), 0.70f);
  m_directionalLight = DirectionalLight(glm::vec3(1, 1, 1), 2.0f,
                                        glm::normalize(glm::vec3(1, -1, -1)));
}

Scene::~Scene() {}

void Scene::Init(std::shared_ptr<Camera> camera) {
  m_camera = camera;

  m_camera->SetPos(glm::vec3(0, 0, 20));
  // m_camera->SetRotate(glm::quat(0, 0, 0, 1));
}

void Scene::Update(float dt) {
  m_camera->HandleInput(dt);
  if (m_spaceShip) {
    m_spaceShip->CheckContacts();
    m_spaceShip->Update(dt);
  }

  for (int i = 0; i < m_projectiles.size(); ++i) {
    m_projectiles[i]->CheckContacts();
    if (m_projectiles[i]->isDestroyRequested()) {
      m_projectiles.erase(m_projectiles.begin() + i);
      --i;
    } else
      m_projectiles[i]->Update(dt);
  }

  for (int i = 0; i < m_asteroids.size(); ++i) {
    if (m_asteroids[i]->isDestroyRequested()) {
      m_asteroids.erase(m_asteroids.begin() + i);
      --i;
    } else
      m_asteroids[i]->Update(dt);
  }
}

void Scene::Reset() {
  std::static_pointer_cast<SpaceShip>(m_spaceShip)->Reset();
  m_projectiles.clear();
  m_asteroids.clear();
}

std::shared_ptr<Camera> Scene::GetCamera() { return m_camera; }
