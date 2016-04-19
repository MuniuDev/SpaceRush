#include "game/AsteroidEmmiter.hpp"
#include "Common.hpp"
#include "game/SpaceShip.hpp"

static const float kSpawnHeight = 10.0f;
static const float kSpawnXOffset = 6.0f;

static const float kMinSize = 0.8f;
static const float kMaxSize = 2.5f;

static const float kXSpeedRange = 1.0f;

static const float kYSpeedMin = 3.5f;
static const float kYSpeedMax = 7.0f;

static const float kRotSpeedRange = 1.6f;

static const float kMaxSpawnInterval = 1.0f;
static const float kMinSpawnInterval = 0.07f;
static const float kSpawnIntervalMantiss = 1.03f;
static const float kSpawnIntervalMult = 1.1f;

float RandomFloat(float min, float max) {
  float ret = min;
  float delta = max - min;
  ret += static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / delta));
  return ret;
}

AsteroidEmmiter::AsteroidEmmiter(std::shared_ptr<Scene> scene)
    : m_scene(scene) {
  m_deltaTime = 0;
}
AsteroidEmmiter::~AsteroidEmmiter() {}

float GetInterval() {
  float ret = (1.0f / std::pow(kSpawnIntervalMantiss, SpaceShip::s_hitCount)) *
              kSpawnIntervalMult;
  return glm::clamp(ret, kMinSpawnInterval, kMaxSpawnInterval);
}

void AsteroidEmmiter::Update(float dt) {
  m_deltaTime += dt;
  float interval = GetInterval();
  if (m_deltaTime >= interval) {
    auto asteroid = std::make_shared<Asteroid>(
        glm::vec3(RandomFloat(-kSpawnXOffset, kSpawnXOffset), kSpawnHeight, 0),
        glm::vec3(RandomFloat(kMinSize, kMaxSize),
                  RandomFloat(kMinSize, kMaxSize),
                  RandomFloat(kMinSize, kMaxSize)),
        glm::vec3(RandomFloat(-kXSpeedRange, kXSpeedRange),
                  RandomFloat(-kYSpeedMin, -kYSpeedMax), 0),
        glm::vec3(RandomFloat(-kRotSpeedRange, kRotSpeedRange),
                  RandomFloat(-kRotSpeedRange, kRotSpeedRange),
                  RandomFloat(-kRotSpeedRange, kRotSpeedRange)));
    asteroid->Init();
    m_scene->m_asteroids.push_back(asteroid);
    m_deltaTime -= interval;
  }
}
