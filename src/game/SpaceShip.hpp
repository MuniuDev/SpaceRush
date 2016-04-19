#pragma once

#include "Common.hpp"
#include "Scene.hpp"
#include "game/PhysicsNode.hpp"
#include "rendering/MeshData.hpp"

class SpaceShip : public PhysicsNode {
 public:
  SpaceShip(std::shared_ptr<Scene> scene);
  ~SpaceShip();

  void Init() override;
  void Update(float dt) override;
  void Draw() override;
  void Reset();
  glm::mat4 GetTransformation() const override;

 public:
  static unsigned int s_hitCount;

 private:
  void Shoot();

  std::shared_ptr<MeshData> m_mesh;
  std::shared_ptr<Scene> m_scene;

  glm::vec3 m_scale;
  glm::quat m_meshRot;
  glm::quat m_rollRot;

  float m_cooldown;
};
