#include "game/PhysicsSimulator.hpp"
#include "game/PhysicsNode.hpp"
#include "game/SpaceShip.hpp"

PhysicsSimulator g_physics;

// Callback structure that handles collision detection logic
struct ContactSensorCallback : public btCollisionWorld::ContactResultCallback {
  btScalar addSingleResult(btManifoldPoint& cp,
                           const btCollisionObjectWrapper* colObj0, int partId0,
                           int index0, const btCollisionObjectWrapper* colObj1,
                           int partId1, int index1) override {
    const OwnedRigidBody* r0 =
        static_cast<const OwnedRigidBody*>(colObj0->m_collisionObject);
    const OwnedRigidBody* r1 =
        static_cast<const OwnedRigidBody*>(colObj1->m_collisionObject);

    if (r0->GetType() == ASTEROID && r1->GetType() == ASTEROID) return 0;
    if (r0->GetType() == PLAYER && r1->GetType() == ASTEROID) {
      // Player-asteroid contact
      auto node = r0->GetOwner();
      if (node) {
        node->Destroy();
      }
    }
    if (r0->GetType() == PROJECTILE && r1->GetType() == ASTEROID) {
      // Projectile-asteroid contact
      auto node0 = r0->GetOwner();
      auto node1 = r1->GetOwner();
      if (node0 && !node0->isDestroyRequested() && node1 &&
          !node1->isDestroyRequested())
        SpaceShip::s_hitCount += 1;
      if (node0) {
        node0->Destroy();
      }
      if (node1) {
        node1->Destroy();
      }
    }
    return 0;
  }
};

PhysicsSimulator::PhysicsSimulator()
    : m_broadphase(new btDbvtBroadphase),
      m_collisionConfiguration(new btDefaultCollisionConfiguration),
      m_dispatcher(new btCollisionDispatcher(m_collisionConfiguration.get())),
      m_solver(new btSequentialImpulseConstraintSolver),
      m_dynamicsWorld(new btDiscreteDynamicsWorld(
          m_dispatcher.get(), m_broadphase.get(), m_solver.get(),
          m_collisionConfiguration.get())) {
  m_dynamicsWorld->setGravity(btVector3(0, 0, 0));
}

void PhysicsSimulator::Update(float dt) {
  m_dynamicsWorld->stepSimulation(dt, 10);
}

void PhysicsSimulator::DebugDraw() {
  if (m_debugRenderer) {
    m_dynamicsWorld->debugDrawWorld();
    m_debugRenderer->Draw();
  }
}

void PhysicsSimulator::AddRigidBody(btRigidBody* body) {
  m_dynamicsWorld->addRigidBody(body);
}

void PhysicsSimulator::RemoveRigidBody(btRigidBody* body) {
  m_dynamicsWorld->removeRigidBody(body);
}

void PhysicsSimulator::AddConstraint(btTypedConstraint* constraint) {
  m_dynamicsWorld->addConstraint(constraint);
}

void PhysicsSimulator::RemoveConstraint(btTypedConstraint* constraint) {
  m_dynamicsWorld->removeConstraint(constraint);
}

void PhysicsSimulator::CheckContacts(btRigidBody* body) {
  static ContactSensorCallback callback;
  m_dynamicsWorld->contactTest(body, callback);
}

void PhysicsSimulator::SetDebugRenderer(
    std::shared_ptr<DebugRenderer> renderer) {
  m_dynamicsWorld->setDebugDrawer(renderer.get());
  m_debugRenderer = renderer;
}
