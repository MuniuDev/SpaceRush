#pragma once

#include "Common.hpp"
#include "INode.hpp"

#include <btBulletDynamicsCommon.h>

enum NodeType { PLAYER, PROJECTILE, ASTEROID };

class PhysicsNode;

class OwnedRigidBody : public btRigidBody {
 public:
  OwnedRigidBody(std::shared_ptr<PhysicsNode> owner, NodeType type,
                 const btRigidBody::btRigidBodyConstructionInfo& info)
      : btRigidBody(info), m_type(type), m_owner(owner) {}
  std::shared_ptr<PhysicsNode> GetOwner() const { return m_owner.lock(); }
  NodeType GetType() const { return m_type; }

 private:
  NodeType m_type;
  std::weak_ptr<PhysicsNode> m_owner;
};

class PhysicsNode : public INode,
                    public std::enable_shared_from_this<PhysicsNode> {
 public:
  PhysicsNode();
  virtual ~PhysicsNode();

  void InitPhysics(std::unique_ptr<btCollisionShape> shape,
                   NodeType nodeType = ASTEROID);
  void Update(float dt) override;
  void Move(const glm::vec3& dir);

  void Destroy() { m_destroyRequested = true; }
  bool isDestroyRequested() override { return m_destroyRequested; }

  void CheckContacts() override;

 protected:
  bool m_destroyRequested;
  glm::vec3 m_pos;
  glm::quat m_rot;

  glm::vec3 m_speed;
  glm::vec3 m_rotSpeed;

  std::unique_ptr<btCollisionShape> m_shape;
  std::unique_ptr<btDefaultMotionState> m_motionState;
  std::unique_ptr<btRigidBody> m_rigidBody;
  std::unique_ptr<btSliderConstraint> m_constraint;
};
