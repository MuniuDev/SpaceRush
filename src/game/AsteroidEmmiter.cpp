#include "game/AsteroidEmmiter.hpp"
#include "Common.hpp"

float RandomFloat(float min, float max) {
  float ret = min;
  float delta = max - min;
  ret += static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / delta));
  return ret;
}

AsteroidEmmiter::AsteroidEmmiter(std::shared_ptr<Scene> scene)
    : m_scene(scene) {
  glm::mat4 inv_mvp = glm::inverse(m_scene->GetCamera()->GetMVP());
  m_border[0] = glm::vec3(inv_mvp * glm::vec4(-1, 1, 0, 1));
  m_border[1] = glm::vec3(inv_mvp * glm::vec4(1, 1, 0, 1) * inv_mvp);
  LOGD("{},{},{} {},{},{}", m_border[0].x, m_border[0].y, m_border[0].z,
       m_border[1].x, m_border[1].y, m_border[1].z);
  m_deltaTime = 0;
}
AsteroidEmmiter::~AsteroidEmmiter() {}

void AsteroidEmmiter::Update(float dt) {
  m_deltaTime += dt;
  if (m_deltaTime >= 0.2) {
    auto asteroid = std::make_shared<Asteroid>(
        glm::vec3(RandomFloat(-6, 6), 10, 0),
        glm::vec3(RandomFloat(0.8, 2), RandomFloat(0.8, 2),
                  RandomFloat(0.8, 2)),
        glm::vec3(RandomFloat(-1, 1), RandomFloat(-3, -6), 0),
        glm::vec3(RandomFloat(-1, 1), RandomFloat(-1, 1), RandomFloat(-1, 1)));
    asteroid->Init();
    m_scene->m_asteroids.push_back(asteroid);
    m_deltaTime -= 0.2;
  }
}
