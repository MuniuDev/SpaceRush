#include "game/PhysicsSimulator.hpp"

PhysicsSimulator g_physics;

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
  LOGD("Adding rigid body to simulation!");
  m_dynamicsWorld->addRigidBody(body);
}

void PhysicsSimulator::RemoveRigidBody(btRigidBody* body) {
  LOGD("Removing rigid body from simulation!");
  m_dynamicsWorld->removeRigidBody(body);
}

void PhysicsSimulator::SetDebugRenderer(
    std::shared_ptr<DebugRenderer> renderer) {
  LOGD("Set debug renderer!");
  m_dynamicsWorld->setDebugDrawer(renderer.get());
  m_debugRenderer = renderer;
}
