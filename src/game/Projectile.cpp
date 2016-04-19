#include "game/Projectile.hpp"

const float kScale = 1.0f;

Projectile::Projectile(const glm::vec3& pos, const glm::vec3& speed) {
  m_pos = pos;
  m_speed = speed;
  m_scale = glm::vec3(kScale * 0.05, kScale * 0.1, kScale * 0.05);
  m_meshRot = glm::angleAxis((float)M_PI_2, glm::vec3(1, 0, 0));
}
Projectile::~Projectile() { MeshFactory::GetInstance().OnRelease(m_mesh); }

void Projectile::Init() {
  m_mesh = MeshFactory::GetInstance().LoadMesh("res/Projectile/",
                                               "projectile.fbx", true);

  InitPhysics(std::unique_ptr<btCollisionShape>(
                  new btBoxShape(btVector3(m_scale.x, m_scale.y, m_scale.z))),
              PROJECTILE);
}
void Projectile::Update(float dt) { PhysicsNode::Update(dt); }
void Projectile::Draw() { m_mesh->Draw(); }

glm::mat4 Projectile::GetTransformation() const {
  glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_scale);
  glm::mat4 trans = glm::translate(glm::mat4(1.0f), m_pos);
  glm::mat4 rot = glm::mat4_cast(m_rot);
  glm::mat4 rot2 = glm::mat4_cast(m_meshRot);
  return trans * rot * scale * rot2;
}
