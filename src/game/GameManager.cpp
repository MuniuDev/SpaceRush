/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "game/GameManager.hpp"
#include "game/SpaceShip.hpp"

GameManager::GameManager(std::shared_ptr<Scene> scene) : m_scene(scene) {}
GameManager::~GameManager() {}

void GameManager::Init() {
  auto ship = std::make_shared<SpaceShip>();
  ship->Init();
  m_scene->m_spaceShip = ship;
}
void GameManager::Reset() {}
void GameManager::Update() { m_scene->Update(g_timer.GetDeltaTime()); }
