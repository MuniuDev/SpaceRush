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
  m_emmiter = std::make_shared<AsteroidEmmiter>(m_scene);

  auto ship = std::make_shared<SpaceShip>(m_scene);
  ship->Init();
  m_scene->m_spaceShip = ship;

#ifdef GAME_DEBUG
  m_debugRenderer = std::make_shared<DebugRenderer>(m_scene->GetCamera());
  g_physics.SetDebugRenderer(m_debugRenderer);
#endif
}

void GameManager::Reset() {}

void GameManager::Update() {
#ifdef GAME_DEBUG
  if (g_input.GetKeyState(SDL_SCANCODE_T))
    m_debugRenderer->setDebugMode(1 | 2);  // wireframe and aabox
  else if (g_input.GetKeyState(SDL_SCANCODE_G))
    m_debugRenderer->setDebugMode(0);  // no draw
#endif

  m_emmiter->Update(g_timer.GetDeltaTime());
  g_physics.Update(g_timer.GetDeltaTime());
  m_scene->Update(g_timer.GetDeltaTime());

  if (m_scene->m_spaceShip->isDestroyRequested()) {
    m_scene->Reset();
  }
}
