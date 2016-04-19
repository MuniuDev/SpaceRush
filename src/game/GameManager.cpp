/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "game/GameManager.hpp"
#include "game/Asteroid.hpp"
#include "game/PhysicsSimulator.hpp"
#include "game/SpaceShip.hpp"

GameManager::GameManager(std::shared_ptr<Scene> scene) : m_scene(scene) {}
GameManager::~GameManager() {}

void GameManager::Init() {
  auto debugRenderer = std::make_shared<DebugRenderer>(m_scene->GetCamera());

  auto ship = std::make_shared<SpaceShip>();
  ship->Init();
  m_scene->m_spaceShip = ship;

  auto asteroid =
      std::make_shared<Asteroid>(glm::vec3(0, 6, 0), glm::vec3(0, -1, 0));
  asteroid->Init();
  m_scene->m_asteroids.push_back(asteroid);

  debugRenderer->setDebugMode(1 | 2);
  g_physics.SetDebugRenderer(debugRenderer);
}
void GameManager::Reset() {}
void GameManager::Update() {
  m_scene->Update(g_timer.GetDeltaTime());
  g_physics.Update(g_timer.GetDeltaTime());
}
