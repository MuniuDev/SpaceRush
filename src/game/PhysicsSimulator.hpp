#pragma once

#include "Common.hpp"

#include <btBulletDynamicsCommon.h>
#include "rendering/DebugRenderer.hpp"

class PhysicsSimulator {
 public:
  PhysicsSimulator();

  void AddRigidBody(btRigidBody* body);
  void AddConstraint(btTypedConstraint* constraint);
  void RemoveRigidBody(btRigidBody* body);
  void RemoveConstraint(btTypedConstraint* constraint);
  void Update(float dt);
  void DebugDraw();
  void SetDebugRenderer(std::shared_ptr<DebugRenderer> renderer);

 private:
  std::unique_ptr<btBroadphaseInterface> m_broadphase;
  std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
  std::unique_ptr<btCollisionDispatcher> m_dispatcher;
  std::unique_ptr<btSequentialImpulseConstraintSolver> m_solver;
  std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicsWorld;

  std::shared_ptr<DebugRenderer> m_debugRenderer;
};

extern PhysicsSimulator g_physics;
