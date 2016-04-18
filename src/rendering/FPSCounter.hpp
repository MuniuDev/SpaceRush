/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#pragma once

#include "Common.hpp"

class FPSCounter {
 public:
  FPSCounter();

  void Tic();
  float GetFPS();

  void Init();
  void Print();

 private:
  uint_t m_frameSum;
  float m_timeSum;
};
