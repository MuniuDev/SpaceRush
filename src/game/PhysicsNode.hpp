#pragma once

#include "Common.hpp"
#include "INode.hpp"

#include <btBulletDynamicsCommon.h>

class PhysicsNode : public INode {
 public:
  PhysicsNode();
  virtual ~PhysicsNode();

  void InitPhysics(std::unique_ptr<btCollisionShape> shape,
                   bool isPlayer = false);
  void Update(float dt) override;
  void Move(const glm::vec3& dir);

 protected:
  glm::vec3 m_pos;
  glm::quat m_rot;

  glm::vec3 m_speed;
  glm::vec3 m_rotSpeed;

  std::unique_ptr<btCollisionShape> m_shape;
  std::unique_ptr<btDefaultMotionState> m_motionState;
  std::unique_ptr<btRigidBody> m_rigidBody;
};
