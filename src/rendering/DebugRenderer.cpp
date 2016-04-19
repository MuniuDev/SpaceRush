/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#include "rendering/DebugRenderer.hpp"

DebugRenderer::DebugRenderer(std::shared_ptr<Camera> camera) {
  m_debugMode = 0;
  m_camera = camera;
  m_shader = std::make_shared<ShaderProgram>("res/debug.vsh", "res/debug.fsh");

  m_shader->RegisterUniform("u_mvp");

  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  glGenBuffers(1, &m_vbo);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float),
               &m_vertices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (const void*)(3 * sizeof(float)));
}
DebugRenderer::~DebugRenderer() {
  // clean up
  glDeleteBuffers(1, &m_vbo);
  glDeleteVertexArrays(1, &m_vao);
}

void DebugRenderer::drawLine(const btVector3& from, const btVector3& to,
                             const btVector3& fromColor,
                             const btVector3& toColor) {
  m_vertices.push_back(from.getX());
  m_vertices.push_back(from.getY());
  m_vertices.push_back(from.getZ());
  m_vertices.push_back(fromColor.getX());
  m_vertices.push_back(fromColor.getY());
  m_vertices.push_back(fromColor.getZ());

  m_vertices.push_back(to.getX());
  m_vertices.push_back(to.getY());
  m_vertices.push_back(to.getZ());
  m_vertices.push_back(toColor.getX());
  m_vertices.push_back(toColor.getY());
  m_vertices.push_back(toColor.getZ());
}

void DebugRenderer::drawLine(const btVector3& from, const btVector3& to,
                             const btVector3& color) {
  drawLine(from, to, color, color);
}

void DebugRenderer::drawSphere(const btVector3& p, btScalar radius,
                               const btVector3& color) {
  // TODO implement
}

void DebugRenderer::drawTriangle(const btVector3& a, const btVector3& b,
                                 const btVector3& c, const btVector3& color,
                                 btScalar alpha) {
  drawLine(a, b, color, color);
  drawLine(b, c, color, color);
  drawLine(a, c, color, color);
}

void DebugRenderer::drawContactPoint(const btVector3& PointOnB,
                                     const btVector3& normalOnB,
                                     btScalar distance, int lifeTime,
                                     const btVector3& color) {
  // TODO implement
}

void DebugRenderer::reportErrorWarning(const char* warningString) {
  LOGE("{}", warningString);
}

void DebugRenderer::draw3dText(const btVector3& location,
                               const char* textString) {
  // TODO implement
}

void DebugRenderer::Draw() {
  // init
  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float),
               &m_vertices[0], GL_STATIC_DRAW);

  // drawing
  m_shader->BindProgram();
  m_shader->SetUniform("u_mvp", m_camera->GetMVP());

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glDrawArrays(GL_LINES, 0, m_vertices.size() / 6);
  glBindVertexArray(0);

  // unbind shader
  glUseProgram(0);
  m_vertices.clear();
}
