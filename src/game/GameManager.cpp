/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "game/GameManager.hpp"

GameManager::GameManager(std::shared_ptr<Scene> scene) : m_scene(scene) {}
GameManager::~GameManager() {}

void GameManager::Init() {}
void GameManager::Reset() {}
void GameManager::Update() {}
