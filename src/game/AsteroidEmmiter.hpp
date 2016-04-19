#pragma once

#include "Scene.hpp"
#include "game/Asteroid.hpp"

class AsteroidEmmiter {
 public:
  AsteroidEmmiter(std::shared_ptr<Scene> scene);
  ~AsteroidEmmiter();

  void Update(float dt);

 private:
  std::shared_ptr<Scene> m_scene;
  glm::vec3 m_border[2];
  float m_deltaTime;
};
