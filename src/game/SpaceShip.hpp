#pragma once

#include "Common.hpp"
#include "INode.hpp"
#include "rendering/MeshFactory.hpp"

class SpaceShip : public INode {
 public:
  SpaceShip();
  ~SpaceShip();

  void Init() override;
  void Update(float dt) override;
  void Draw() override;
  glm::mat4 GetTransformation() const override;

 private:
  std::shared_ptr<MeshData> m_mesh;

  glm::vec3 m_pos;
  glm::vec3 m_scale;
  glm::quat m_rot;
};
