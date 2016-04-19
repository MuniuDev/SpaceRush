#include "game/Asteroid.hpp"

#include <cmath>

const float kScale = 0.5f;

Asteroid::Asteroid(const glm::vec3& pos, const glm::vec3& speed) {
  m_pos = pos;
  m_speed = speed;
}

Asteroid::~Asteroid() { MeshFactory::GetInstance().OnRelease(m_mesh); }

void Asteroid::Init() {
  m_mesh = MeshFactory::GetInstance().LoadMesh("res/Asteroid/", "asteroid.fbx");
  m_scale = glm::vec3(kScale);

  InitPhysics(std::unique_ptr<btCollisionShape>(
      new btBoxShape(btVector3(m_scale.x, m_scale.y, m_scale.z))));
}

void Asteroid::Update(float dt) { PhysicsNode::Update(dt); }

void Asteroid::Draw() { m_mesh->Draw(); }

glm::mat4 Asteroid::GetTransformation() const {
  glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_scale);
  glm::mat4 trans = glm::translate(glm::mat4(1.0f), m_pos);
  glm::mat4 rot = glm::mat4_cast(m_rot);
  return trans * rot * scale;
}
