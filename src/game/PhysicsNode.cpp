#include "game/PhysicsNode.hpp"
#include "game/PhysicsSimulator.hpp"

PhysicsNode::PhysicsNode() {}
PhysicsNode::~PhysicsNode() {
  if (m_rigidBody) g_physics.RemoveRigidBody(m_rigidBody.get());
}

void PhysicsNode::InitPhysics(std::unique_ptr<btCollisionShape> shape,
                              bool isPlayer) {
  // Setup physics
  m_shape = std::move(shape);
  float mass = 1.0f;

  btVector3 inertia;
  m_shape->calculateLocalInertia(mass, inertia);

  m_motionState =
      std::unique_ptr<btDefaultMotionState>(new btDefaultMotionState(
          btTransform(btQuaternion(m_rot.x, m_rot.y, m_rot.z, m_rot.w),
                      btVector3(m_pos.x, m_pos.y, m_pos.z))));

  btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
      mass, m_motionState.get(), m_shape.get(), inertia);
  m_rigidBody = std::unique_ptr<btRigidBody>(new btRigidBody(rigidBodyCI));

  // set 2D plane contraints
  if (isPlayer) {
    m_rigidBody->setLinearFactor(btVector3(1, 0, 0));
    m_rigidBody->setAngularFactor(btVector3(0, 0, 0));
  } else {
    m_rigidBody->setLinearFactor(btVector3(1, 1, 0));
    m_rigidBody->setAngularFactor(btVector3(1, 1, 1));
  }

  // setup default values
  m_rigidBody->setLinearVelocity(btVector3(m_speed.x, m_speed.y, m_speed.z));
  m_rigidBody->setAngularVelocity(
      btVector3(m_rotSpeed.x, m_rotSpeed.y, m_rotSpeed.z));

  m_rigidBody->setDamping(0, 0);

  g_physics.AddRigidBody(m_rigidBody.get());
}

void PhysicsNode::Move(const glm::vec3& dir) {
  if (glm::length(dir) > 0) {
    m_rigidBody->setDamping(0.2, m_rigidBody->getAngularDamping());
    m_rigidBody->applyImpulse(btVector3(dir.x, dir.y, dir.z),
                              btVector3(0, 0, 0));
  } else {
    m_rigidBody->setDamping(0.95, m_rigidBody->getAngularDamping());
  }
}

void PhysicsNode::Update(float dt) {
  m_rigidBody->activate(true);
  btTransform trans;
  m_motionState->getWorldTransform(trans);
  const btQuaternion& rot = trans.getRotation();
  const btVector3& pos = trans.getOrigin();
  m_rot = glm::quat(rot.getW(), rot.getX(), rot.getY(), rot.getZ());
  m_pos = glm::vec3(pos.getX(), pos.getY(), pos.getZ());

  const btVector3& vel = m_rigidBody->getLinearVelocity();
  const btVector3& angVel = m_rigidBody->getLinearVelocity();
  m_speed = glm::vec3(vel.getX(), vel.getY(), vel.getZ());
  m_rotSpeed = glm::vec3(angVel.getX(), angVel.getY(), angVel.getZ());
}
