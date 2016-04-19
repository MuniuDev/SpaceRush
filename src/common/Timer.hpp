/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#pragma once

#include <chrono>

#include "Common.hpp"

class Timer {
 public:
  void Init();
  void Tic();
  float GetDeltaTime();
  float GetTotalTime();

 private:
  std::chrono::time_point<std::chrono::system_clock> m_lastTicTimePoint;
  float m_lastDeltaTime;
  float m_totalTime;
};

extern Timer g_timer;
