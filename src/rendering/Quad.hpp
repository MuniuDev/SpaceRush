/*
* Copyright by Michal Majczak, 2016
* Licensed under the MIT license:
* http://www.opensource.org/licenses/mit-license.php
*
* Author: Michal Majczak <michal.majczak92@gmail.com>
*/

#pragma once

#include <Common.hpp>

class Quad {
 public:
  Quad() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);

    GLfloat vertices[] = {1.0f,  1.0f,  0.0f, 1.0f,  1.0f, -1.0f, 1.0f, 0.0f,
                          0.0f,  1.0f,  1.0f, -1.0f, 0.0f, 1.0f,  0.0f, -1.0f,
                          -1.0f, 0.0f,  0.0f, 0.0f,  1.0f, -1.0f, 0.0f, 1.0f,
                          0.0f,  -1.0f, 1.0f, 0.0f,  0.0f, 1.0f};

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                          (const void*)(3 * sizeof(GLfloat)));

    glBindVertexArray(0);
  }

  ~Quad() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
  }
  void Render() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
  }

 private:
  GLuint vao, vbo;
};
