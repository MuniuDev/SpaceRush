/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "game/GameManager.hpp"
#include "common/Input.hpp"
#include "game/Asteroid.hpp"
#include "game/PhysicsSimulator.hpp"
#include "game/SpaceShip.hpp"

GameManager::GameManager(std::shared_ptr<Scene> scene) : m_scene(scene) {}
GameManager::~GameManager() {}

void GameManager::Init() {
  m_debugRenderer = std::make_shared<DebugRenderer>(m_scene->GetCamera());

  m_emmiter = std::make_shared<AsteroidEmmiter>(m_scene);

  auto ship = std::make_shared<SpaceShip>(m_scene);
  ship->Init();
  m_scene->m_spaceShip = ship;

  g_physics.SetDebugRenderer(m_debugRenderer);
}
void GameManager::Reset() {}
void GameManager::Update() {
  if (g_input.GetKeyState(SDL_SCANCODE_T))
    m_debugRenderer->setDebugMode(1 | 2);
  else if (g_input.GetKeyState(SDL_SCANCODE_G))
    m_debugRenderer->setDebugMode(0);

  m_emmiter->Update(g_timer.GetDeltaTime());
  m_scene->Update(g_timer.GetDeltaTime());
  g_physics.Update(g_timer.GetDeltaTime());
}
