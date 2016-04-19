#include "game/SpaceShip.hpp"
#include "game/Projectile.hpp"

#include <cmath>

const float kMoveSpeed = 0.3f;
const float kScale = 0.03f;

const float kWidth = 37.0f;
const float kLength = 35.0f;
const float kHeight = 10.0f;

SpaceShip::SpaceShip(std::shared_ptr<Scene> scene) : m_scene(scene) {}

SpaceShip::~SpaceShip() { MeshFactory::GetInstance().OnRelease(m_mesh); }

void SpaceShip::Init() {
  m_mesh =
      MeshFactory::GetInstance().LoadMesh("res/SpaceShip/", "spaceship.fbx");
  m_pos = glm::vec3(0, -6, 0);
  m_scale = glm::vec3(kScale);
  m_meshRot = glm::angleAxis((float)-M_PI_2, glm::vec3(0, 0, 1)) *
              glm::angleAxis((float)M_PI_2, glm::vec3(1, 0, 0));

  // InitPhysics(
  //  std::unique_ptr<btCollisionShape>(new btBoxShape(btVector3(1, 1, 1))),
  // true);
  InitPhysics(std::unique_ptr<btCollisionShape>(
                  new btConeShape(kWidth * 0.5f * kScale, kLength * kScale)),
              PLAYER);
}

void SpaceShip::Update(float dt) {
  PhysicsNode::Update(dt);

  m_cooldown += dt;
  // handle input
  glm::vec3 move;
  if (g_input.GetKeyState(SDL_SCANCODE_LEFT))
    move.x = -1;
  else if (g_input.GetKeyState(SDL_SCANCODE_RIGHT))
    move.x = 1;
  // TODO disable y motion
  if (g_input.GetKeyState(SDL_SCANCODE_UP))
    move.y = 1;
  else if (g_input.GetKeyState(SDL_SCANCODE_DOWN))
    move.y = -1;
  Move(glm::normalize(move) * kMoveSpeed);

  if (g_input.GetKeyState(SDL_SCANCODE_SPACE)) {
    Shoot();
  }
}

void SpaceShip::Draw() { m_mesh->Draw(); }

glm::mat4 SpaceShip::GetTransformation() const {
  glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_scale);
  glm::mat4 trans = glm::translate(glm::mat4(1.0f), m_pos);
  glm::mat4 rot = glm::mat4_cast(m_rot * m_meshRot);
  return trans * rot * scale;
}

void SpaceShip::Shoot() {
  if (m_cooldown > 0.5f) {
    LOGD("Shoot!");
    auto p = std::make_shared<Projectile>(m_pos + glm::vec3(0, 1, 0),
                                          glm::vec3(0, 5, 0));
    p->Init();
    m_scene->m_projectiles.push_back(p);
    m_cooldown = 0.0f;
  }
}
