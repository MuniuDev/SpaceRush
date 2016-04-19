#include "game/Asteroid.hpp"

#include <cmath>

const float kScale = 0.3f;

Asteroid::Asteroid(const glm::vec3& pos, const glm::vec3& scale,
                   const glm::vec3& speed, const glm::vec3& rotSpeed) {
  m_pos = pos;
  m_speed = speed;
  m_rotSpeed = rotSpeed;
  m_scale = scale * kScale;
}

Asteroid::~Asteroid() { MeshFactory::GetInstance().OnRelease(m_mesh); }

void Asteroid::Init() {
  m_mesh = MeshFactory::GetInstance().LoadMesh("res/Asteroid/", "asteroid.fbx");

  InitPhysics(std::unique_ptr<btCollisionShape>(
                  new btBoxShape(btVector3(m_scale.x, m_scale.y, m_scale.z))),
              ASTEROID);
}

void Asteroid::Update(float dt) { PhysicsNode::Update(dt); }

void Asteroid::Draw() { m_mesh->Draw(); }

glm::mat4 Asteroid::GetTransformation() const {
  glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_scale);
  glm::mat4 trans = glm::translate(glm::mat4(1.0f), m_pos);
  glm::mat4 rot = glm::mat4_cast(m_rot);
  return trans * rot * scale;
}
