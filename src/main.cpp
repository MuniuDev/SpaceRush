/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "Common.hpp"
#include "game/GameManager.hpp"
#include "rendering/Context.hpp"

int main() {
  srand((unsigned int)time(NULL));

  auto context = std::make_shared<Context>(500, 800, "SpaceRush");
  auto scene = std::make_shared<Scene>();
  auto gameMgr = std::make_shared<GameManager>(scene);
  context->Init(scene);
  gameMgr->Init();
  g_timer.Init();

  while (!context->ShouldClose()) {
    g_timer.Tic();
    context->PollEvents();
    gameMgr->Update();
    context->Draw();
  }

  return 0;
}
