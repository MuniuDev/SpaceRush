#pragma once

#include "Common.hpp"
#include "INode.hpp"
#include "game/PhysicsNode.hpp"
#include "rendering/MeshFactory.hpp"

class SpaceShip : public PhysicsNode {
 public:
  SpaceShip();
  ~SpaceShip();

  void Init() override;
  void Update(float dt) override;
  void Draw() override;
  glm::mat4 GetTransformation() const override;

 private:
  std::shared_ptr<MeshData> m_mesh;

  glm::vec3 m_scale;
  glm::quat m_meshRot;
};
