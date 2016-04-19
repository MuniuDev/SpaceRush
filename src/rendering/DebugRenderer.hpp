/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#pragma once

#include <btBulletDynamicsCommon.h>
#include "Scene.hpp"
#include "rendering/ShaderProgram.hpp"

#include <vector>

class DebugRenderer : public btIDebugDraw {
 public:
  DebugRenderer(std::shared_ptr<Camera> camera);
  virtual ~DebugRenderer();

  void drawLine(const btVector3& from, const btVector3& to,
                const btVector3& fromColor, const btVector3& toColor) override;

  void drawLine(const btVector3& from, const btVector3& to,
                const btVector3& color) override;

  void drawSphere(const btVector3& p, btScalar radius,
                  const btVector3& color) override;

  void drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c,
                    const btVector3& color, btScalar alpha) override;

  void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB,
                        btScalar distance, int lifeTime,
                        const btVector3& color) override;

  void reportErrorWarning(const char* warningString) override;

  void draw3dText(const btVector3& location, const char* textString) override;

  void setDebugMode(int debugMode) override { m_debugMode = debugMode; }

  int getDebugMode() const override { return m_debugMode; }

  void Draw();

 private:
  int m_debugMode;
  std::shared_ptr<ShaderProgram> m_shader;
  std::shared_ptr<Camera> m_camera;
  std::vector<float> m_vertices;
  GLuint m_vao, m_vbo;
};
