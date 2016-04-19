#pragma once

#include "Common.hpp"
#include "INode.hpp"
#include "Scene.hpp"
#include "game/PhysicsNode.hpp"
#include "rendering/MeshFactory.hpp"

class SpaceShip : public PhysicsNode {
 public:
  SpaceShip(std::shared_ptr<Scene> scene);
  ~SpaceShip();

  void Init() override;
  void Update(float dt) override;
  void Draw() override;
  void Reset();
  glm::mat4 GetTransformation() const override;

 private:
  void Shoot();

  std::shared_ptr<MeshData> m_mesh;
  std::shared_ptr<Scene> m_scene;

  glm::vec3 m_scale;
  glm::quat m_meshRot;

  float m_cooldown;
};
