#pragma once

#include "Common.hpp"
#include "game/PhysicsNode.hpp"
#include "rendering/MeshFactory.hpp"

#include <btBulletDynamicsCommon.h>

class Asteroid : public PhysicsNode {
 public:
  Asteroid(const glm::vec3& pos, const glm::vec3& speed);
  ~Asteroid();

  void Init() override;
  void Update(float dt) override;
  void Draw() override;
  glm::mat4 GetTransformation() const override;

 private:
  std::shared_ptr<MeshData> m_mesh;

  glm::vec3 m_scale;
};
