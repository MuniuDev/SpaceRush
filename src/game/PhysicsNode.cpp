#include "game/PhysicsNode.hpp"
#include "game/PhysicsSimulator.hpp"

static const float kShipXLimit = 5.3f;
static const float kShipMoveDamping = 0.3f;
static const float kShipStopDamping = 0.98f;

static const float kOutOffScreenBordeer = 25.0f;

OwnedRigidBody::OwnedRigidBody(
    std::shared_ptr<PhysicsNode> owner, NodeType type,
    const btRigidBody::btRigidBodyConstructionInfo& info)
    : btRigidBody(info), m_type(type), m_owner(owner) {}

PhysicsNode::PhysicsNode() : m_destroyRequested(false) {}
PhysicsNode::~PhysicsNode() {
  if (m_constraint) g_physics.RemoveConstraint(m_constraint.get());
  if (m_rigidBody) g_physics.RemoveRigidBody(m_rigidBody.get());
}

void PhysicsNode::InitPhysics(std::unique_ptr<btCollisionShape> shape,
                              NodeType nodeType, float mass) {
  // Setup physics
  m_shape = std::move(shape);

  btVector3 inertia(0, 0, 0);
  if (mass > 0) m_shape->calculateLocalInertia(mass, inertia);

  m_motionState =
      std::unique_ptr<btDefaultMotionState>(new btDefaultMotionState(
          btTransform(btQuaternion(m_rot.x, m_rot.y, m_rot.z, m_rot.w),
                      btVector3(m_pos.x, m_pos.y, m_pos.z))));

  btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
      mass, m_motionState.get(), m_shape.get(), inertia);
  m_rigidBody = std::unique_ptr<btRigidBody>(
      new OwnedRigidBody(shared_from_this(), nodeType, rigidBodyCI));

  // set 2D plane contraints
  if (nodeType == PLAYER) {
    // can only move on X axis, no rotation
    m_rigidBody->setLinearFactor(btVector3(1, 0, 0));
    m_rigidBody->setAngularFactor(btVector3(0, 0, 0));
  } else if (nodeType == PROJECTILE) {
    // can only move on Y axis, no rotation
    m_rigidBody->setLinearFactor(btVector3(0, 1, 0));
    m_rigidBody->setAngularFactor(btVector3(0, 0, 0));
  } else {  // asteroid
    // can move frelly (X and Y axis), with 3DOF in rotation
    m_rigidBody->setLinearFactor(btVector3(1, 1, 0));
    m_rigidBody->setAngularFactor(btVector3(1, 1, 1));
  }

  // setup default values
  m_rigidBody->setLinearVelocity(btVector3(m_speed.x, m_speed.y, m_speed.z));
  m_rigidBody->setAngularVelocity(
      btVector3(m_rotSpeed.x, m_rotSpeed.y, m_rotSpeed.z));

  m_rigidBody->setDamping(0, 0);
  m_rigidBody->setActivationState(DISABLE_DEACTIVATION);

  g_physics.AddRigidBody(m_rigidBody.get());

  // add ship constraint to ensure not leaving the screen
  if (nodeType == PLAYER) {
    btTransform t;
    t.setIdentity();
    m_constraint = std::unique_ptr<btSliderConstraint>(
        new btSliderConstraint(*(m_rigidBody.get()), t, true));
    m_constraint->setLowerLinLimit(-kShipXLimit);
    m_constraint->setUpperLinLimit(kShipXLimit);
    g_physics.AddConstraint(m_constraint.get());
  }
}

void PhysicsNode::Move(const glm::vec3& dir) {
  if (glm::length(dir) > 0) {
    m_rigidBody->setDamping(kShipMoveDamping, m_rigidBody->getAngularDamping());
    m_rigidBody->applyImpulse(btVector3(dir.x, dir.y, dir.z),
                              btVector3(0, 0, 0));
  } else {
    m_rigidBody->setDamping(kShipStopDamping, m_rigidBody->getAngularDamping());
  }
}

void PhysicsNode::Update(float dt) {
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

  if (m_pos.y < -kOutOffScreenBordeer || m_pos.y > kOutOffScreenBordeer ||
      m_pos.x < -kOutOffScreenBordeer || m_pos.x > kOutOffScreenBordeer) {
    m_destroyRequested = true;
  }
}

void PhysicsNode::CheckContacts() {
  g_physics.CheckContacts(m_rigidBody.get());
}
