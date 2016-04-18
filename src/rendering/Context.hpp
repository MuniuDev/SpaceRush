/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#pragma once

#include "Common.hpp"
#include "rendering/FPSCounter.hpp"
#include "rendering/Viewport.hpp"

#include <vector>

class Context {
 public:
  Context(float width, float height, std::string name);
  virtual ~Context();

  void Init(std::shared_ptr<Scene> scene);
  void Draw();
  void PollEvents();

  bool ShouldClose() { return m_shouldClose; }

 private:
  void HandleWindowEvent(const SDL_Event &event);
  void SwapBuffers();

  // Viewports
  Viewport m_viewport;

  float m_width;
  float m_height;

  FPSCounter m_fpsCounter;

  // SDL
  SDL_Window *m_window;
  SDL_GLContext m_context;

  bool m_shouldClose;
};
