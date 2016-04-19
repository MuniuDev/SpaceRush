/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "rendering/FPSCounter.hpp"

static const float kInterval = 1.0f;

FPSCounter::FPSCounter() {}

void FPSCounter::Init() {
  m_frameSum = 0;
  m_timeSum = 0.0f;
}

void FPSCounter::Tic() {
  m_frameSum += 1;
  m_timeSum += g_timer.GetDeltaTime();
}

float FPSCounter::GetFPS() { return m_frameSum / m_timeSum; }

void FPSCounter::Print() {
  // update fps every second
  if (m_timeSum >= kInterval) {
    LOGD("FPS: {}", GetFPS());
    m_timeSum -= kInterval;
    m_frameSum = 0;
  }
}
