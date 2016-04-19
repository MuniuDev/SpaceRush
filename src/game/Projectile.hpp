#pragma once

#include "Common.hpp"
#include "game/PhysicsNode.hpp"
#include "rendering/MeshData.hpp"

class Projectile : public PhysicsNode {
 public:
  Projectile(const glm::vec3& pos, const glm::vec3& speed);
  ~Projectile();

  void Init() override;
  void Update(float dt) override;
  void Draw() override;
  glm::mat4 GetTransformation() const override;

 private:
  std::shared_ptr<MeshData> m_mesh;

  glm::vec3 m_scale;
  glm::quat m_meshRot;
};
