/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "Timer.hpp"

#include <limits>

void Timer::Init() {
  m_lastTicTimePoint = std::chrono::system_clock::now();
  m_lastDeltaTime = std::numeric_limits<float>::max();
  m_totalTime = 0.0f;
}

void Timer::Tic() {
  auto tmp = std::chrono::system_clock::now();
  std::chrono::duration<float> deltaTime = tmp - m_lastTicTimePoint;
  m_lastTicTimePoint = tmp;
  m_lastDeltaTime = deltaTime.count();
  m_totalTime += m_lastDeltaTime;
}

float Timer::GetDeltaTime() { return m_lastDeltaTime; }
float Timer::GetTotalTime() { return m_totalTime; }

Timer g_timer;
